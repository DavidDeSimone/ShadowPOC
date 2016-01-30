#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 ModelViewProjection;
uniform mat4 ModelView;
uniform mat4 Model;

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;

void main()
{
    gl_Position = ModelViewProjection * vec4(position, 1.0); // See how we directly give a vec3 to vec4's constructor
    Normal = normal;
    TexCoords = texCoords;
    FragPos = vec3(Model * vec4(position, 1.0));
}