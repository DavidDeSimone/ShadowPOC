#version 330 core
#define MAX_POINT_LIGHTS 32

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPos;
in vec4 FragPosLightSpace[MAX_POINT_LIGHTS];

out vec4 color;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_specular;

uniform sampler2D shadow_maps[MAX_POINT_LIGHTS];

uniform vec3 view_dir;

struct point_light
{
    vec3 pos;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;
};

uniform int num_point_lights = 0;


uniform point_light point_light_arr[MAX_POINT_LIGHTS];

float shadow_calc(vec4 frag_pos_light_space, int index)
{
    vec3 proj_corrds = frag_pos_light_space.xyz / frag_pos_light_space.w;
    proj_corrds = proj_corrds * 0.5f + 0.5; // map from [0,1] to [-1,1]
    float closest_depth = texture(shadow_maps[0], proj_corrds.xy).r;
    float current_depth = proj_corrds.z;
    float shadow = current_depth > closest_depth ? 100.0 : 0.0;
    return shadow;
}

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

vec3 calc_point_light(point_light point, vec3 norm, vec3 vd, int index)
{
    vec3 light_dir = normalize(point.pos - FragPos);
    
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(vd, reflect_dir), 0.0), 64.0f);
    float distance = length(point.pos - FragPos);
    float attenuation = 1.0f / (point.constant + point.linear * distance +
                                point.quadratic * (distance * distance));
    
    vec3 ambient  = point.ambient  * vec3(texture(texture_diffuse, TexCoords));
    vec3 diffuse  = point.diffuse  * diff * vec3(texture(texture_diffuse, TexCoords));
    vec3 specular = point.specular * spec * vec3(texture(texture_specular, TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    float shadow_val = shadow_calc(FragPosLightSpace[0], index);
    vec3 shadow_m_ds = (1.0f - shadow_val) * (diffuse + specular);
    return (ambient + shadow_m_ds);
}


void main()
{
    vec3 norm = normalize(Normal);
    vec3 vd = normalize(view_dir - FragPos);
    vec3 dir_light = calc_dir_light(norm, vd);
    
    vec3 p_light = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < num_point_lights; ++i)
    {
        p_light += calc_point_light(point_light_arr[i], norm, vd, i);
    }
        
    color = vec4(dir_light + p_light, 1.0f);
}