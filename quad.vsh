#version 330 core

layout (location = 0) in vec2 position; 
layout (location = 1) in vec2 texCoords;

uniform mat4 ModelViewProjection;

out vec2 TexCoords;

void main()
{
    gl_Position = ModelViewProjection * vec4(position.x, position.y, 0.0, 1.0);
    TexCoords = texCoords;
}