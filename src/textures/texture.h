#pragma once
#include "../common/types.h"

class texture
{
public:
    virtual vec3 fetch(const vec2& uv, const vec3 point) const = 0;
};
