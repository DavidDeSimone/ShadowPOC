//
//  Cube.hpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "glew.h"
#include <stdio.h>
#include <memory>
#include "glm.hpp"
#include "CAShaderProgram.h"
#include "CATexture2D.h"
constexpr int MAX_MAP = 6;
class cube
{
public:
    cube();
    cube(float x, float y, float z);
    ~cube() = default;
    
    void draw();
    static void init();
    
    glm::vec3 pos, scale;
    float rotation;
    
    void set_texture(const std::string& name, TEXTURE_TYPE type);
    
    
private:
    static GLuint cube_vao, cube_vbo;
    static shader_program cube_shader;
    static GLuint mvp_loc;
    
    // array of diff maps, array of spec maps
    texture_2D d_maps[MAX_MAP]; size_t d_count;
    texture_2D s_maps[MAX_MAP]; size_t s_count;
};

#endif /* Cube_hpp */
