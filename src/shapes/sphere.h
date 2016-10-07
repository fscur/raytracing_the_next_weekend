#pragma once

#include "shape.h"
#include "../materials/material.h"

class sphere :
    public shape
{
public:
    sphere(vec3 center, float radius, material* material);

    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& aabb) const override;

private:
    vec2 getUv(const vec3& point) const;

private:
    vec3 _center;
    float _radius;
    material* _material;
};


