#include "movingSphere.h"

movingSphere::movingSphere(
    vec3 c0,
    vec3 c1,
    float t0,
    float t1,
    float radius, 
    material* material, 
    std::function<vec3(float)> movementFunction) :
    _c0(c0),
    _c1(c1),
    _t0(t0),
    _t1(t1),
    _radius(radius),
    _material(material),
    _movementFunction(movementFunction)
{
}

bool movingSphere::hit(const ray& ray, float tMin, float tMax, intersection& hitRecord) const
{
    vec3 center = getCenter(ray.time);
    vec3 oc = ray.origin - center;

    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - (_radius*_radius);
    float discriminant = b * b - a * c;

    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hitRecord.t = temp;
            hitRecord.point = ray.pointAtParameter(temp);
            hitRecord.normal = (hitRecord.point - center) / _radius;
            hitRecord.material = _material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hitRecord.t = temp;
            hitRecord.point = ray.pointAtParameter(temp);
            hitRecord.normal = (hitRecord.point - center) / _radius;
            hitRecord.material = _material;
            return true;
        }
    }

    return false;
}

vec3 movingSphere::getCenter(float time) const
{
    return _c0 + ((time - _t0) / (_t1 - _t0)) * (_c1 - _c0);
}
