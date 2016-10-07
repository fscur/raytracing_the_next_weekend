#include "sphere.h"

sphere::sphere(vec3 center, float radius, material* material) :
    _center(center),
    _radius(radius),
    _material(material)
{
}

bool sphere::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    vec3 oc = ray.origin - _center;

    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - _radius * _radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.pointAtParameter(temp);
            hit.normal = (hit.point - _center) / _radius;
            hit.material = _material;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.pointAtParameter(temp);
            hit.normal = (hit.point - _center) / _radius;
            hit.material = _material;
            return true;
        }
    }

    return false;
}

bool sphere::createBoundingBox(float t0, float t1, aabb& a) const
{
    vec3 r = vec3(_radius, _radius, _radius);
    a = aabb(_center - r, _center + r);
    return true;
}
