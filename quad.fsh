#version 330 core

out vec4 color;
in vec2 TexCoords;

uniform sampler2D quad_texture;

void main()
{
    color = vec4(texture(renderTex, TexCoords));
}