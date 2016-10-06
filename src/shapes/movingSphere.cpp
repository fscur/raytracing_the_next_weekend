#include "movingSphere.h"

movingSphere::movingSphere(
    float radius, 
    material* material, 
    std::function<vec3(float)> movementFunction) :
    _radius(radius),
    _material(material),
    _movementFunction(movementFunction)
{
}

bool movingSphere::hit(const ray& ray, float tMin, float tMax, intersection& hitRecord) const
{
    vec3 center = _movementFunction(ray.time);
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
