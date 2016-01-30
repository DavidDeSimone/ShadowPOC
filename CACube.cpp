//
//  Cube.cpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CACube.h"
#include "CACamera.h"
#include "CAUtil.h"

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

GLuint cube::cube_vao = 0;
GLuint cube::cube_vbo = 0;
shader_program cube::cube_shader;
cuniforms cube::cube_uniforms = {0};
GLuint cube::d_loc[MAX_MAP];
GLuint cube::s_loc[MAX_MAP];


static constexpr float cube_vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

cube::cube() : pos(0.0,0.0,0.0), scale(1.0,1.0,1.0), rotation(0.0)
{
}
cube::cube(float x, float y, float z) : pos(x, y, z), scale(1.0, 1.0, 1.0), rotation(45.0)
{
}

void cube::set_texture(const std::string& name, TEXTURE_TYPE type)
{
    if (type == TEXTURE_TYPE::DIFFUSE)
    {
        assert(d_map.size() <= MAX_MAP);
        d_map.emplace_back(texture_2D(name));
    }
    else if (type == TEXTURE_TYPE::SPECULAR)
    {
        assert(s_map.size() <= MAX_MAP);
        s_map.emplace_back(texture_2D(name));
    }
}

void cube::init()
{
    glGenVertexArrays(1, &cube_vao);
    glBindVertexArray(cube_vao);
    
    glGenBuffers(1, &cube_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 6));
    
    auto cube_vts = make_shader("mesh.vsh", GL_VERTEX_SHADER);
    auto cube_fsh = make_shader("mesh.fsh", GL_FRAGMENT_SHADER);
    cube_shader.attachShader(cube_vts);
    cube_shader.attachShader(cube_fsh);
    cube_shader.link();
    
    cube_shader.use();
    cube_uniforms.mvp_loc = glGetUniformLocation(cube_shader.get(), "ModelViewProjection");
    cube_uniforms.mv_loc  = glGetUniformLocation(cube_shader.get(), "ModelView");
    cube_uniforms.m_loc   = glGetUniformLocation(cube_shader.get(), "Model");
    cube_uniforms.view_loc = glGetUniformLocation(cube_shader.get(), "view_dir");
    d_loc[0] = glGetUniformLocation(cube_shader.get(), "texture_diffuse");
    s_loc[0] = glGetUniformLocation(cube_shader.get(), "texture_specular");
}

void cube::draw()
{
    cube_shader.use();
    glBindVertexArray(cube_vao);
    
    auto camera = get_default_camera();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)get_width() / get_height(), 0.1f, 100.f);
    glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
    
    auto model = glm::mat4();
    model = glm::translate(model, pos);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0));
    
    glm::mat4 mvp = projection * view * model;
    glm::mat4 mv  = view * model;
    glUniformMatrix4fv(cube_uniforms.mvp_loc, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(cube_uniforms.mv_loc, 1, GL_FALSE, glm::value_ptr(mv));
    glUniformMatrix4fv(cube_uniforms.m_loc, 1, GL_FALSE, glm::value_ptr(model));
    
    glUniform3f(cube_uniforms.view_loc, camera.pos.x, camera.pos.y, camera.pos.z);
    
    d_map[0].bind(d_loc[0], 0);
    s_map[0].bind(s_loc[0], 1);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(0);
}