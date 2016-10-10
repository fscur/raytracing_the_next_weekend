#pragma once
#include "../textures/texture.h"
#include "material.h"

class emissive :
    public material
{
public:
    emissive(texture* albedo);
    virtual bool scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const;
    virtual vec3 emitted(const vec2& uv, const vec3& point) const;
private:
    texture* _albedo;
};


