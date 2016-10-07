#pragma once
#include "../math/ray.h"
#include "../math/intersection.h"
#include "../math/aabb.h"

class shape
{
public:
    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const = 0;
    virtual bool createBoundingBox(float t0, float t1, aabb& aabb) const = 0;
};