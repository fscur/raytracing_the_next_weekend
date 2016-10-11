#pragma once
#include <functional>

#include "shape.h"
#include "../materials/material.h"

class movingSphere :
    public shape
{
public:
    movingSphere(
        vec3 center,
        float radius,
        float speed,
        material* material,
        std::function<vec3(vec3, float, float)> movementFunction);

    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& aabb) const override;

    vec2 getUv(const vec3 & point) const;

private:
    vec3 _center;
    float _speed;
    float _radius;
    material* _material;
    std::function<vec3(vec3, float, float)> _movementFunction;
};


