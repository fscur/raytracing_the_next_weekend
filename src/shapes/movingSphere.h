#pragma once
#include <functional>

#include "shape.h"
#include "../materials/material.h"

class movingSphere :
    public shape
{
public:
    movingSphere(
        vec3 c0,
        vec3 c1,
        float t0,
        float t1,
        float radius,
        material* material,
        std::function<vec3(float)> movementFunction);

    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;

private:
    vec3 getCenter(float time) const;

private:
    vec3 _c0;
    vec3 _c1;
    float _t0;
    float _t1;
    float _radius;
    material* _material;
    std::function<vec3(float)> _movementFunction;
};


