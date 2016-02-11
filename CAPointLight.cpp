//
//  CAPointLight.cpp
//  ShadowPOC
//
//  Created by David on 1/31/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAPointLight.h"
#include "CAScene.h"
#include "CACube.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

void point_light::bind(GLuint shader, int index)
{
    if (!lazy_init) set_uniform_locs(shader, index); lazy_init = true;
    glUniform3f(point_light_uniforms.u_position, pos.x, pos.y, pos.z);
    glUniform3f(point_light_uniforms.u_ambient, ambient.x, ambient.y, ambient.z);
    glUniform3f(point_light_uniforms.u_diffuse, diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(point_light_uniforms.u_specular, specular.x, specular.y, specular.z);
    glUniform1f(point_light_uniforms.u_constant, constant);
    glUniform1f(point_light_uniforms.u_linear, linear);
    glUniform1f(point_light_uniforms.u_quadratic, quadratic);
    glUniformMatrix4fv(point_light_uniforms.u_ls_matrix, 1, GL_FALSE, glm::value_ptr(transform()));
    
    // TODO hard coding 16 wont SCALE
    depth_texture.bind(point_light_uniforms.u_shadow_maps_arr, index + 16);
}

void point_light::set_uniform_locs(GLuint shader, int index)
{
    std::string base_str = std::string("point_light_arr[") + std::to_string(index) + std::string("].");
    std::string mat_str = std::string("SpaceLightMatrixArray[") + std::to_string(index) + std::string("]");
    std::string shadow_map_arr_str = std::string("shadow_maps[") + std::to_string(index) + std::string("]");
    std::string pos_str = base_str + "pos";
    std::string am_str = base_str + "ambient";
    std::string df_str = base_str + "diffuse";
    std::string sp_str = base_str + "specular";
    std::string cs_str = base_str + "constant";
    std::string ln_str = base_str + "linear";
    std::string qud_str = base_str + "quadratic";
    point_light_uniforms.u_position = glGetUniformLocation(shader, pos_str.c_str());
    point_light_uniforms.u_ambient = glGetUniformLocation(shader, am_str.c_str());
    point_light_uniforms.u_diffuse = glGetUniformLocation(shader, df_str.c_str());
    point_light_uniforms.u_specular = glGetUniformLocation(shader, sp_str.c_str());
    point_light_uniforms.u_constant = glGetUniformLocation(shader, cs_str.c_str());
    point_light_uniforms.u_linear = glGetUniformLocation(shader, ln_str.c_str());
    point_light_uniforms.u_quadratic = glGetUniformLocation(shader, qud_str.c_str());
    point_light_uniforms.u_ls_matrix = glGetUniformLocation(shader, mat_str.c_str());
    point_light_uniforms.u_shadow_maps_arr = glGetUniformLocation(shader, shadow_map_arr_str.c_str());
}

void point_light::draw(float dt)
{
    //TODO make this use render_texture_2D
    light_program.use();
    glViewport(0, 0, shadow_width, shadow_height);
    glBindFramebuffer(GL_FRAMEBUFFER, light_FBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(point_light_uniforms.u_lightMVP, 1, GL_FALSE, glm::value_ptr(transform()));
    // Issue: Rendered scene needs to use the light program shader, and not bind uniforms
    glCullFace(GL_FRONT);
    for (auto & c : get_current_scene().get())
    {
        c->draw();
    }
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, get_width(), get_height());
}

glm::mat4 point_light::transform()
{
    auto projection = glm::ortho(-10.f, 10.f, -10.f, 10.f, 1.0f, 7.5f);
    auto view = glm::lookAt(pos, glm::vec3(0.0f), glm::vec3(1.0));
    
    return projection * view;
}

texture_2D& point_light::get()
{
    return depth_texture;
}

void point_light::init_texture()
{
    glGenFramebuffers(1, &light_FBO);
    GLuint depth_map;
    glGenTextures(1, &depth_map);
    glBindTexture(GL_TEXTURE_2D, depth_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glBindFramebuffer(GL_FRAMEBUFFER, light_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    light_program.attachShader(make_shader("depthMap.vsh", GL_VERTEX_SHADER));
    light_program.attachShader(make_shader("depthMap.fsh", GL_FRAGMENT_SHADER));
    light_program.link();
    
    point_light_uniforms.u_lightMVP = glGetUniformLocation(light_program.get(), "lightSpaceMatrix");
    
    depth_texture.set(depth_map);
}