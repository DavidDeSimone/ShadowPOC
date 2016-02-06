//
//  CAQuad.hpp
//  ShadowPOC
//
//  Created by David on 2/4/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CAQuad_hpp
#define CAQuad_hpp

#include <stdio.h>
#include "CATexture2D.h"
#include "CAShaderProgram.h"
#include "CAUtil.h"
#include "glm.hpp"
#include "glew.h"

struct quad_uniforms
{
    GLuint u_mvp;
    GLuint u_texture;
};

class quad
{
public:
    quad() : pos(0.0, 0.0, 0.0), scale(1.0, 1.0, 1.0), rotation(0.0) {};
    quad(float x, float y, float z) : pos(x, y, z), scale(1.0, 1.0, 1.0), rotation(0.0) {};
    ~quad() = default;
    void draw(float dt);
    glm::vec3 pos;
    glm::vec3 scale;
    float rotation;
    
    
    
    void set_texture(texture_2D&& tex);
    
    static void init();
    
private:
    texture_2D texture;
    static quad_uniforms uniforms;
    static GLuint quad_vao, quad_vbo;
    static shader_program program;
};

#endif /* CAQuad_hpp */
