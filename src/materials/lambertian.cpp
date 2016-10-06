#include "../common/sampler.h"

#include "lambertian.h"

lambertian::lambertian(const vec3& albedoColor) :
    _albedoColor(albedoColor)
{
}

bool lambertian::scatter(const ray& r, const intersection& hit, glm::vec3& attenuation, ray& scattered) const
{
    vec3 target = hit.point + hit.normal + sampler::randomPositionInUnitSphere();
    scattered = ray(hit.point, target - hit.point);
    attenuation = _albedoColor;
    return true;
}
