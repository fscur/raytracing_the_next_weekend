#include "../samplers/sampler.h"

#include "lambertian.h"

lambertian::lambertian(texture* albedo) :
    _albedo(albedo)
{
}

bool lambertian::scatter(const ray& r, const intersection& hit, glm::vec3& attenuation, ray& scattered) const
{
    vec3 target = hit.point + hit.normal + sampler::randomPositionInUnitSphere();
    scattered = ray(hit.point, target - hit.point, r.time);
    attenuation = _albedo->fetch(hit.uv, hit.point);
    return true;
}
