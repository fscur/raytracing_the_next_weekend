#pragma once
#include "../common/types.h"

class material;

struct intersection
{
    float t;
    vec3 point;
    vec3 normal;
    vec2 uv;
    material* material;
};