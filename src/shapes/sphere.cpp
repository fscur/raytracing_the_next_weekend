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
            hit.uv = getUv(hit.normal);
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hit.t = temp;
            hit.point = ray.pointAtParameter(temp);
            hit.normal = (hit.point - _center) / _radius;
            hit.material = _material;
            hit.uv = getUv(hit.normal);
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

vec2 sphere::getUv(const vec3& point) const
{
    float phi = atan2(point.z, point.x);
    float theta = asin(point.y);
    float u = 1.0f - (phi + glm::pi<float>()) / glm::two_pi<float>();
    float v = (theta + glm::half_pi<float>()) / glm::pi<float>();
    return vec2(u, v);
}
