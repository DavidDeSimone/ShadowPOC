//
//  main.cpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#include <iostream>
#include "glew.h"
#include "glfw3.h"
#include "CACamera.h"
#include "CACube.h"
#include "CAUtil.h"
#include "CAScene.h"
#include "CAPointLight.h"
#include "CAQuad.h"

constexpr int width = 800;
constexpr int height = 600;

void start(GLFWwindow *window);
void update(float dt);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

camera default_camera;
scene base_scene;

int main(int argc, const char * argv[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Shadow POC", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glViewport(0, 0, width, height);
    cube::init();
    quad::init();
    
    base_scene.add(new (std::nothrow) cube( 0.0f,  1.5f,  0.0f));
    base_scene.add(new (std::nothrow) cube( 2.0f,  5.0f, 1.0f));
    base_scene.add(new (std::nothrow) cube(-1.0f, 0.0f, 2.0f));
    base_scene.add(new (std::nothrow) cube(-3.8f, -2.0f, -12.3f));
    base_scene.add(new (std::nothrow) cube( 2.4f, -0.4f, -3.5f));
    base_scene.add(new (std::nothrow) cube(-1.7f,  3.0f, -7.5f));
    base_scene.add(new (std::nothrow) cube( 1.3f, -2.0f, -2.5f));
    base_scene.add(new (std::nothrow) cube( 1.5f,  2.0f, -2.5f));
    base_scene.add(new (std::nothrow) cube( 1.5f,  0.2f, -1.5f));
    base_scene.add(new (std::nothrow) cube(-1.3f,  1.0f, -1.5f));
    
    for (auto cube : base_scene.get()) {
        cube->set_texture("specular.png", TEXTURE_TYPE::SPECULAR);
        cube->set_texture("wood.png", TEXTURE_TYPE::DIFFUSE);
    }
    
    auto floor = new (std::nothrow) cube(0.0, -3.f, 0.0);
    floor->set_scale(20.0, 0.1, 20.0);
    floor->set_texture("specular.png", TEXTURE_TYPE::SPECULAR);
    floor->set_texture("wood_panel.png", TEXTURE_TYPE::DIFFUSE);
    base_scene.add(floor);
    
    base_scene.add(new (std::nothrow) point_light(0.0, 3.0, 2.0));
    base_scene.add(new (std::nothrow) point_light(1.0, 2.0, 1.0));
    base_scene.add(new (std::nothrow) point_light(0.0, 3.0, 0.0));
    
    start(window);
    
    return 0;
}

void start(GLFWwindow *window)
{
    float last_frame = glfwGetTime();
    while (true)
    {
        float current_frame = glfwGetTime();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        update(current_frame - last_frame);
        glfwSwapBuffers(window);
        last_frame = current_frame;
    }
}

void update(float dt)
{
    base_scene.lighting_pass(dt);
    base_scene.renderq(dt);
    base_scene.render(dt);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    default_camera.update_mov(key);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    default_camera.update_pos(xpos, ypos);
}

int get_width()
{
    return width;
}

int get_height()
{
    return height;
}

camera get_default_camera()
{
    return default_camera;
}

scene& get_current_scene()
{
    return base_scene;
}
