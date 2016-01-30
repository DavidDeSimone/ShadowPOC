#version 330 core
in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;

out vec4 color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

uniform vec3 view_dir;

vec3 calc_dir_light(vec3 norm, vec3 vd)
{
    vec3 light_direction = vec3(-0.2f, -1.0f, -0.3f);
    vec3 ambient = vec3(0.05f, 0.05f, 0.05f);
    vec3 diffuse = vec3(0.4f, 0.4f, 0.4f);
    vec3 specular = vec3(0.5f, 0.5f, 0.5f);
    
    vec3 ld = normalize(-light_direction);
    float diff = max(dot(norm, ld), 0.0);
    
    vec3 reflect_dir = reflect(-ld, norm);
    float spec = pow(max(dot(vd, reflect_dir), 0.0), 64.0);
    
    vec3 al = ambient * vec3(texture(texture_diffuse, TexCoords));
    vec3 dl = diffuse * diff * vec3(texture(texture_diffuse, TexCoords));
    vec3 sl = specular * spec * vec3(texture(texture_specular, TexCoords));
    
    return (al + dl + sl);
}

void main()
{
    vec3 norm = normalize(Normal);
    vec3 vd = normalize(view_dir - FragPos);
    vec3 dir_light = calc_dir_light(norm, vd);
    
    color = vec4(dir_light, 1.0f);
//    color = vec4(texture(texture_diffuse, TexCoords)) + vec4(texture(texture_specular, TexCoords));
}