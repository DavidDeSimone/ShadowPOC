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

struct cuniforms
{
    GLuint mvp_loc;
    GLuint mv_loc;
    GLuint m_loc;
    GLuint view_loc;
    GLuint num_point_lights;
};


class cube
{
public:
    cube();
    cube(float x, float y, float z);
    ~cube() = default;
    
    void visit(float dt);
    void draw();
    static void init();
    
    glm::vec3 pos, scale;
    float rotation;
    
    void set_scale(float x, float y, float z);
    void set_rotation(float r);
    
    void set_texture(const std::string& name, TEXTURE_TYPE type);
    
    
private:
    void set_pl_uniforms() const;
    
    
    static GLuint cube_vao, cube_vbo;
    static shader_program cube_shader;
    static cuniforms cube_uniforms;
    
    // array of diff maps, array of spec maps
    std::vector<texture_2D> d_map;
    std::vector<texture_2D> s_map;
    static GLuint d_loc[MAX_MAP]; static GLuint s_loc[MAX_MAP];
    
    bool visible;
};

#endif /* Cube_hpp */
