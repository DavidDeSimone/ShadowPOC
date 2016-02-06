//
//  CAShaderProgram.hpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#ifndef CAShaderProgram_hpp
#define CAShaderProgram_hpp

#include <iostream>
#include "glew.h"
#include <vector>
#include "CAUtil.h"
#include <assert.h>

#define __shaderdir std::string("/Users/david//Desktop/ShadowPOC/")

class shader_program {
public:
    inline shader_program()
    {
        _program = 0;
    }
    
    inline void attachShader(GLuint shader)
    {
        if (!_program) _program = glCreateProgram();
        shaders.push_back(shader);
        glAttachShader(_program, shader);
    }
    
    inline void link()
    {
        glLinkProgram(_program);
        for (auto shader : shaders)
        {
            glDetachShader(_program, shader);
            glDeleteShader(shader);
        }
    }
    
    inline void use()
    {
        assert(_program != 0);
        glUseProgram(_program);
    }
    
    inline GLuint get()
    {
        return _program;
    }
    
private:
    std::vector<GLuint> shaders;
    GLuint _program;
};

inline GLuint make_shader(const std::string& shader_name, GLenum gl_shader_type)
{
    GLuint shader = glCreateShader(gl_shader_type);
    char* shader_src = read_file_contents(__shaderdir + shader_name);
    // Fill in shader source, and compile
    glShaderSource(shader, 1, &shader_src, NULL);
    glCompileShader(shader);
    
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" <<  "NAME::\n" << shader_name << std::endl << infoLog << std::endl;
    }
    
    free (shader_src);
    
    return shader;
}





#endif /* CAShaderProgram_hpp */
