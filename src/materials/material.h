#pragma once
#include "../shapes/shape.h"

class material
{
public:
    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const = 0;
    virtual vec3 emitted(const vec2& uv, const vec3& point) const
    {
        return vec3(0.0f);
    }
};


