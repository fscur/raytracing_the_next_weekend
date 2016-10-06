#pragma once
#include "../common/types.h"

class ray
{
public:
    ray()
    {}

    ray(const vec3& origin, const vec3& direction, float time):
        origin(origin),
        direction(direction),
        time(time)
    {
    }

    vec3 pointAtParameter(float t) const
    {
        return origin + t * direction;
    }

    vec3 origin;
    vec3 direction;
    float time;
};
