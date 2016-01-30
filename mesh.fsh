#version 330 core
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

void main()
{
    color = vec4(texture(texture_diffuse, TexCoords)) + vec4(texture(texture_specular, TexCoords));
}