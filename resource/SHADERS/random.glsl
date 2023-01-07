#ifndef RANDOM_GLSL
#define RANDOM_GLSL

float random_num(vec2 coef){
    return fract(sin(dot(coef.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

float random(){
    return random_num(frag_pos.xy);
}

vec2 random2(){
    return vec2(random(), random());
}

vec3 random3(){
    return vec3(random(), random(), random());
}

#endif