#pragma once

#include "material.h"

class metal :
    public material
{
public:
    metal(const vec3& albedoColor, float roughness);
    bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const;

private:
    vec3 _albedoColor;
    float _roughness;
};


