#version 330 core

in vec3 _normal;
in vec3 _frag_pos;

out vec4 color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main()

{
    float ambient_strength = 0.1f;
    float specular_strength = 0.5;

    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(_normal);
    vec3 light_direction = normalize(light_pos - _frag_pos);

    float diff = max(dot(norm, light_direction), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 view_direction = normalize(view_pos - _frag_pos);
    vec3 reflect_direction = reflect(-light_direction, norm);

    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;

    vec3 result = (ambient + diffuse + specular) * object_color;
    color = vec4(result, 1.0f);
}
