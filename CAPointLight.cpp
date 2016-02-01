//
//  CAPointLight.cpp
//  ShadowPOC
//
//  Created by David on 1/31/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CAPointLight.h"

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
}

void point_light::set_uniform_locs(GLuint shader, int index)
{
    std::string base_str = std::string("point_lights[") + std::to_string(index) + std::string("].");
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
}