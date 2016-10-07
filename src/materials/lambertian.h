#pragma once
#include "../textures/texture.h"
#include "material.h"

class lambertian :
    public material
{
public:
    lambertian(texture* albedo);
    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const;

private:
    texture* _albedo;
};


