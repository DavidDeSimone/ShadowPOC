//
//  CAPointLight.hpp
//  ShadowPOC
//
//  Created by David on 1/31/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CAPointLight_hpp
#define CAPointLight_hpp

#include "glew.h"
#include <stdio.h>
#include "CAUtil.h"
#include "CAShaderProgram.h"
#include "CATexture2D.h"
#include "glm.hpp"

struct puniforms
{
    GLuint u_position;
    GLuint u_ambient;
    GLuint u_diffuse;
    GLuint u_specular;
    GLuint u_constant;
    GLuint u_linear;
    GLuint u_quadratic;
    
    GLuint u_lightMVP;
};

class point_light
{
public:
    point_light() : pos(0, 0, 0), lazy_init(false),
    ambient(1.0, 1.0, 1.0),
    diffuse(1.0, 1.0, 1.0),
    specular(1.0, 1.0, 1.0),
    constant(1.0),
    linear(1.0),
    quadratic(1.0)
    {
        init_texture();
    };
    
    point_light(float x, float y, float z) :
    pos(x, y, z),
    lazy_init(false),
    ambient(1.0, 1.0, 1.0),
    diffuse(1.0, 1.0, 1.0),
    specular(1.0, 1.0, 1.0),
    constant(1.0),
    linear(1.0),
    quadratic(1.0)
    {
        init_texture();
    };
    
    ~point_light() = default;
    point_light(const point_light& cpy) = delete;
    point_light(point_light&& mv) = delete;
    
    //TODO make a texture 2d
    void draw(float dt);
    texture_2D& get();
    
    void bind(GLuint shader, int index);
    
    glm::vec3 pos;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
    
    static constexpr int shadow_width = 1024;
    static constexpr int shadow_height = 1024;
    
private:
    bool lazy_init;
    void set_uniform_locs(GLuint shader, int index);
    puniforms point_light_uniforms;
    shader_program light_program;
    
    GLuint light_FBO;
    
    texture_2D depth_texture;
    
    void init_texture();
    void transform();
};

#endif /* CAPointLight_hpp */
