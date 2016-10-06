#pragma once
#include "../common/types.h"

class material;

struct intersection
{
    float t;
    glm::vec3 point;
    glm::vec3 normal;
    material* material;
};