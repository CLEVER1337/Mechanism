#ifndef RIGID_BODY_GLSL
#define RIGID_BODY_GLSL

#version 330 core

struct s_material{
    vec3 emmitance;
    vec3 reflectance;
    float roughness;
    float opacity;
};

struct s_rigid_body{
    s_material material;
    vec3 position;
};

#endif