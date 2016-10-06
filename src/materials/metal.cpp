#include "metal.h"
#include "../common/sampler.h"
#include "../math/vmath.h"

metal::metal(const vec3& albedoColor, float roughness) :
    _albedoColor(albedoColor),
    _roughness(roughness)
{
    if (_roughness > 1.0f)
        _roughness = 1.0f;
}

bool metal::scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const
{
    vec3 reflectionDirection = vMath::reflect(normalize(r.direction), hit.normal);
    scattered = ray(hit.point, reflectionDirection + _roughness * sampler::randomPositionInUnitSphere());
    attenuation = _albedoColor;
    return dot(scattered.direction, hit.normal) > 0.0f;
}
