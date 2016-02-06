//
//  CATexture2D.cpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CATexture2D.h"
#include "glew.h"
#include "SOIL.h"
#include <assert.h>


#define __texturedir std::string("/Users/david//Desktop/ShadowPOC/textures/")

std::map<std::string, texture_count> texture_2D::texture_cache;

texture_2D::texture_2D(const std::string& tname)
:name(tname),
external(false)
{
    auto tc_iter = texture_cache.find(tname);
    if (tc_iter != texture_cache.end())
    {
        tc_iter->second.count++;
        texture = tc_iter->second.texture;
    } else {
        texture = make_texture(tname.c_str());
        texture_count tc_insert = {texture, 1};
        texture_cache.insert(std::make_pair(tname, tc_insert));
    }
}

texture_2D::~texture_2D()
{
    if (external)
    {
        glDeleteTextures(1, &texture);
        return;
    }
    
    if (!name.length()) return; // in case the move constructor has stolen our name :)
    auto tc_iter = texture_cache.find(name);
    assert(tc_iter != texture_cache.end());
    
    auto tc_insert = tc_iter->second;
    tc_insert.count--;
    if (!tc_insert.count)
    {
        texture_cache.erase(name);
        glDeleteTextures(1, &tc_insert.texture);
    }

}

void texture_2D::set(GLuint tex)
{
    assert(tex != 0);
    texture = tex;
    external = true;
}

texture_2D::texture_2D(const texture_2D& copy)
:name(copy.name)
{
    auto tc_iter = texture_cache.find(name);
    assert(tc_iter != texture_cache.end());
    tc_iter->second.count++;
    texture = tc_iter->second.texture;
}

GLuint texture_2D::make_texture(const char *name)
{
    int width, height;
    std::string path = __texturedir + name;
    unsigned char *data = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    SOIL_free_image_data(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return texture;
}

void texture_2D::bind(GLuint loc, int num)
{
    assert(texture != 0);
    glActiveTexture(GL_TEXTURE0 + num);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(loc, num);
//    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint texture_2D::get() const
{
    assert(texture != 0);
    return texture;
}