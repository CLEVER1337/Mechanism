#ifndef RANDOM_GLSL
#define RANDOM_GLSL

float random(vec2 coef){
    return fract(sin(dot(coef.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

#endif