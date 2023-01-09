#ifndef REFRACTION_GLSL
#define REFRACTION_GLSL

float schlick_approximation(float refractive_index_in, float refractive_index_out, vec3 direction, vec3 normal){
    float R0 = ((refractive_index_out - refractive_index_in) * (refractive_index_out - refractive_index_in)) / ((refractive_index_out + refractive_index_in) * (refractive_index_out + refractive_index_in));
    float reflection_coef = R0 + (1.0 - R0) * pow((1.0 - abs(dot(direction, normal))), 5.0);
    return reflection_coef;
}

vec3 ideal_refract(vec3 direction, vec3 normal, float refractive_index_in, float refractive_index_out){
    bool from_outside = dot(normal, direction) < 0.0;
    float ratio = from_outside ? refractive_index_out / refractive_index_in : refractive_index_in / refractive_index_out;

    vec3 refraction = from_outside ? refract(direction, normal, ratio) : -refract(-direction, normal, ratio);
    vec3 reflection = reflect(direction, normal);

    return refraction == vec3(0.0) ? reflection : refraction;
}

bool is_refracted(vec3 direction, vec3 normal, float refractive_index_in, float refractive_index_out, float rand, float opacity){
    float coef = schlick_approximation(refractive_index_in, refractive_index_out, direction, normal);
    return opacity > rand ? && coef < rand;
}

#endif