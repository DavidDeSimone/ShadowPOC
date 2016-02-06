//
//  CAQuad.cpp
//  ShadowPOC
//
//  Created by David on 2/4/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAQuad.h"

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

quad_uniforms quad::uniforms;
GLuint quad::quad_vao = 0;
GLuint quad::quad_vbo = 0;
shader_program quad::program;

static constexpr GLfloat quadVertices[] = {
    // Positions   // TexCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    
    -1.0f,  1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f, 1.0f
};

void quad::draw(float dt)
{
    program.use();
    texture.bind(uniforms.u_texture, 0);
    glBindVertexArray(quad_vao);
    
    auto model_view = glm::mat4();
    model_view = glm::translate(model_view, pos);
    model_view = glm::scale(model_view, scale);
    model_view = glm::rotate(model_view, glm::radians(rotation), glm::vec3(1.0f));
    
    auto projection = glm::ortho(0.0f, static_cast<float>(get_width()), static_cast<float>(get_height()), 0.0f, -1.0f, 100.0f);
    auto mvp = projection * model_view;
    
    glUniformMatrix4fv(uniforms.u_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
}

void quad::init()
{
    glGenBuffers(1, &quad_vbo);
    glGenVertexArrays(1, &quad_vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glBindVertexArray(quad_vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 2));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    program.attachShader(make_shader("quad.vsh", GL_VERTEX_SHADER));
    program.attachShader(make_shader("quad.fsh", GL_FRAGMENT_SHADER));
    program.link();
    
    uniforms.u_mvp = glGetUniformLocation(program.get(), "ModelViewProjection");
    uniforms.u_texture = glGetUniformLocation(program.get(), "quad_texture");
}
