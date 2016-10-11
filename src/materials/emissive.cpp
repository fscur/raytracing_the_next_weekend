#include "../samplers/sampler.h"

#include "emissive.h"

emissive::emissive(texture* albedo) :
    _albedo(albedo)
{
}

bool emissive::scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const
{
    return false;
}

vec3 emissive::emitted(const vec2 & uv, const vec3 & point) const
{
    return _albedo->fetch(uv, point);
}
