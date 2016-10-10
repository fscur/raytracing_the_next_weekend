#pragma once
#include "material.h"
#include "../textures/texture.h"
#include "../samplers/sampler.h"

class isotropic : 
    public material {
public:
    isotropic(texture* albedo) : 
        _albedo(albedo) 
    {
    }

    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const 
    {
        scattered = ray(hit.point, sampler::randomPositionInUnitSphere(), r.time);
        attenuation = _albedo->fetch(hit.uv, hit.point);
        return true;
    }
private:
    texture* _albedo;
};
