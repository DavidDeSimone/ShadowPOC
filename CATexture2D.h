//
//  CATexture2D.hpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CATexture2D_hpp
#define CATexture2D_hpp

#include <stdio.h>
#include <map>
#include <string>
#include "glew.h"

enum class TEXTURE_TYPE
{
    SPECULAR,
    DIFFUSE
};

struct texture_count
{
    GLuint texture;
    size_t count;
};

class texture_2D
{
public:
    texture_2D() : texture(0) {};
    texture_2D(const std::string& name);
    ~texture_2D();
    GLuint get() const;
    
private:
    static std::map<std::string, texture_count> texture_cache;
    static GLuint make_texture(const char * name);
    GLuint texture;
    std::string name;
};

#endif /* CATexture2D_hpp */
