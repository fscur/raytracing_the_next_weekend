#include "movingSphere.h"

movingSphere::movingSphere(
    vec3 center,
    float radius, 
    float speed,
    material* material, 
    std::function<vec3(vec3, float, float)> movementFunction) :
    _center(center),
    _speed(speed),
    _radius(radius),
    _material(material),
    _movementFunction(movementFunction)
{
}

bool movingSphere::hit(const ray& ray, float tMin, float tMax, intersection& hitRecord) const
{
    vec3 center = _movementFunction(_center, ray.time, _speed);
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

bool movingSphere::createBoundingBox(float t0, float t1, aabb& a) const
{
    vec3 r = vec3(_radius);
    auto c0 = _movementFunction(_center, t0, _speed);
    auto c1 = _movementFunction(_center, t1, _speed);

    auto aabb0 = aabb(c0 - r, c0 + r);
    auto aabb1 = aabb(c1 - r, c1 + r);

    a = aabb::getSurroundingAabb(aabb0, aabb1);
    return true;
}