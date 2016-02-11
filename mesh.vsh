#version 330 core
#define MAX_POINT_LIGHTS 32

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform int num_point_lights = 0;

uniform mat4 ModelViewProjection;
uniform mat4 ModelView;
uniform mat4 Model;
uniform mat4 SpaceLightMatrixArray[MAX_POINT_LIGHTS];

out vec3 Normal;
out vec2 TexCoords;
out vec3 FragPos;
out vec4 FragPosLightSpace[MAX_POINT_LIGHTS];

void main()
{
    gl_Position = ModelViewProjection * vec4(position, 1.0f); // See how we directly give a vec3 to vec4's constructor
    Normal = normal;
    TexCoords = texCoords;
    FragPos = vec3(Model * vec4(position, 1.0f));
    FragPosLightSpace[0] = SpaceLightMatrixArray[0] * vec4(FragPos, 1.0f);
}