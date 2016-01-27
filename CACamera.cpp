//
//  Camera.cpp
//  ShadowPOC
//
//  Created by David on 1/24/16.
//  Copyright © 2016 David. All rights reserved.
//

#include "CACamera.h"
#include "glfw3.h"
#include <iostream>

void camera::update_pos(double x, double y)
{
    static bool first_mouse = true;
    
    if (first_mouse) {
        lastX = x;
        lastY = y;
        first_mouse = false;
    }
    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x; lastY = y;
    
    constexpr float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw += xoffset;
    pitch += yoffset;
    
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    
    glm::vec3 ft;
    ft.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    ft.y = sin(glm::radians(pitch));
    ft.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(ft);
}

void camera::update_mov(int key)
{
    float cameraSpeed = 0.5f;
    if(key == GLFW_KEY_W)
        pos += cameraSpeed * front;
    if(key == GLFW_KEY_S)
        pos -= cameraSpeed * front;
    if(key == GLFW_KEY_A)
        pos -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
    if(key == GLFW_KEY_D)
        pos += glm::normalize(glm::cross(front, up)) * cameraSpeed;
}