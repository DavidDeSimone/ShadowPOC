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
#include "glm.hpp"
#include "CAShaderProgram.h"

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
private:
    static GLuint cube_vao, cube_vbo;
    static shader_program cube_shader;
    static GLuint mvp_loc;
};

#endif /* Cube_hpp */
