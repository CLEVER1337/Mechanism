#version 330 core

#include "ray.glsl"
#include "rigid_body.glsl"

#define FAR_DISTANCE 1000000.0

uniform int u_object_count;

s_rigid_body objects[u_object_count];

bool ray_cast(s_ray ray, out float distance_to_object, out vec3 normal, s_material material){
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