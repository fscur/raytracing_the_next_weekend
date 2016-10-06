#pragma once

#include "material.h"

class dielectric :
    public material
{
public:
    dielectric(float refractionIndex);
    bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const;
private:
    float _indexOfRefraction;
};


