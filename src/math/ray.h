//
// Created by Filipe on 01/10/2016.
//

#pragma once
#include "../common/types.h"

class ray
{
public:
    ray()
    {}

    ray(const glm::vec3& origin, const glm::vec3& direction):
        origin(origin),
        direction(direction)
    {
    }

    glm::vec3 pointAtParameter(float t) const
    {
        return origin + t * direction;
    }

    glm::vec3 origin;
    glm::vec3 direction;
};
