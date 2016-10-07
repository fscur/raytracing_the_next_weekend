#include "metal.h"
#include "../samplers/sampler.h"
#include "../math/vmath.h"

metal::metal(texture* albedo, float roughness) :
    _albedo(albedo),
    _roughness(roughness)
{
    if (_roughness > 1.0f)
        _roughness = 1.0f;
}

bool metal::scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const
{
    vec3 reflectionDirection = vMath::reflect(normalize(r.direction), hit.normal);
    scattered = ray(hit.point, reflectionDirection + _roughness * sampler::randomPositionInUnitSphere(), r.time);
    attenuation = _albedo->fetch(hit.uv, hit.point);
    return dot(scattered.direction, hit.normal) > 0.0f;
}
