#pragma once

#include "material.h"

class lambertian :
    public material
{
public:
    lambertian(const vec3& albedoColor);
    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const;

private:
    vec3 _albedoColor;
};


