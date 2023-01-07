#version 330 core

#define FAR_DISTANCE 1000000.0
#define MAX_REFLECTIONS 8

uniform int u_object_count;

in vec3 frag_pos;

s_rigid_body objects[u_object_count];

#include "ray.glsl"
#include "rigid_body.glsl"
#include "reflection.glsl"

bool ray_cast(s_ray ray, out float distance_to_object, out vec3 normal, out s_material material){
    float min_distance = FAR_DISTANCE;

    for(int i = 0; i < u_object_count; i++){
        float out_distance;
        vec3 out_normal;
        if(ray_intersection(ray, objects[i], out_distance, out_normal) && out_distance < min_distance){
            min_distance = out_distance;
            normal = out_normal;
            material = objects[i].material;
        }
    }

    distance_to_object = min_distance;
    return min_distance != FAR_DISTANCE;
}

vec3 path_trace(s_ray ray){
    vec3 total_light = vec3(0.0);
    vec3 reflection_coef = vec3(1.0);

    for(int i = 0; i < MAX_REFLECTIONS; i++){
        float distance_to_object;
        vec3 normal;
        s_material material;
        s_ray new_ray;

        if(ray_cast(ray, distance_to_object, normal, material)){
            new_ray.origin = ray.origin + distance_to_object * ray.direction;
            
            vec3 hemisphere_distributed_direction = get_random_hemisphere_ray_relative_normal(random2(), normal);

            random_vec = normalize(2.0 * random3() - 1.0);

            vec3 tangent = cross(random_vec, normal);
            vec3 bitangent = cross(normal, tangent);
            mat3 transform = mat3(tangent, bitangent, normal);

            new_ray.direction = transform * hemisphere_distributed_direction;

            vec3 ideal_reflection = reflect(ray.direction, normal);
            new_ray.direction = normalize(mix(new_ray.direction, ideal_reflection, material.roughness));

            new_ray.origin += normal * 0.8;

            ray.origin = new_ray.origin;
            ray.direction = new_ray.direction;

            total_light += reflection_coef * material.emmitance;
            reflection_coef *= material.reflectance;
        }
        else{
            reflection_coef = vec3(0.0);
        }
    }

    return total_light;
}