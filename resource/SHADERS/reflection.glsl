#ifndef REFLECTION_GLSL
#define REFLECTION_GLSL

#define PI 3.1415926535

#include "random.glsl"

vec3 get_random_hemisphere_ray(vec2 rand){
    float cos_theta = sqrt(1.0 - rand.x);
    float sin_theta = sqrt(rand.x);
    float phi = 2.0 * PI * rand.y;
    
    return vec3(cos(phi) * sin_theta, sin(phi) * sin_theta, cos_theta);
}

vec3 get_random_hemisphere_ray_relative_normal(vec2 rand, vec3 normal){
    vec3 ray = get_random_hemisphere_ray(rand);

    return dot(ray, normal) < 0.0 ? -ray : ray;
}

#endif