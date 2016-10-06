#pragma once
#include "../shapes/shape.h"

class material
{
public:
    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const = 0;
};


