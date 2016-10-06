#include "sphere.h"

sphere::sphere(vec3 center, float radius, material* mat) :
    center(center),
    radius(radius),
    mat(mat)
{
}

bool sphere::hit(const ray& ray, float tMin, float tMax, intersection& hitRecord) const
{
    vec3 oc = ray.origin - center;

    float a = dot(ray.direction, ray.direction);
    float b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;

    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hitRecord.t = temp;
            hitRecord.point = ray.pointAtParameter(temp);
            hitRecord.normal = (hitRecord.point - center) / radius;
            hitRecord.material = mat;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < tMax && temp > tMin)
        {
            hitRecord.t = temp;
            hitRecord.point = ray.pointAtParameter(temp);
            hitRecord.normal = (hitRecord.point - center) / radius;
            hitRecord.material = mat;
            return true;
        }
    }

    return false;
}