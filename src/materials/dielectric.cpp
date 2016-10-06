#include "../common/random.h"
#include "../math/vmath.h"

#include "dielectric.h"

dielectric::dielectric(float indexOfRefraction) :
    _indexOfRefraction(indexOfRefraction)
{}

bool dielectric::scatter(const ray& r, const intersection& hit, vec3& attenuation, ray& scattered) const
{
    vec3 outwardNormal;
    vec3 reflected = vMath::reflect(r.direction, hit.normal);
    float eta;
    attenuation = vec3(1.0f, 1.0f, 1.0f);
    vec3 refracted;
    float reflectionProbability;
    float cosine;
    float incidenceAngle = dot(r.direction, hit.normal);

    if (incidenceAngle > 0.0f)
    {
        outwardNormal = -hit.normal;
        eta = _indexOfRefraction;
        cosine = _indexOfRefraction * incidenceAngle / length(r.direction);
    }
    else
    {
        outwardNormal = hit.normal;
        eta = 1.0f/_indexOfRefraction;
        cosine = -incidenceAngle / length(r.direction);
    }

    if (vMath::refract(r.direction, outwardNormal, eta, refracted))
        reflectionProbability = vMath::schlick(cosine, _indexOfRefraction);
    else
        reflectionProbability = 1.0f;

    if (random::next() < reflectionProbability)
    {
        scattered = ray(hit.point, reflected);
    }
    else
    {
        scattered = ray(hit.point, refracted);
    }

    return true;
}