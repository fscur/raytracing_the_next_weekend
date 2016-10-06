#pragma once
#include <functional>

#include "shape.h"
#include "../materials/material.h"

class movingSphere :
    public shape
{
public:
    movingSphere(
        float radius,
        material* material,
        std::function<vec3(float)> movementFunction);

    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;

private:
    //vec3 getCenter(float time) const;

private:
    float _radius;
    material* _material;
    std::function<vec3(float)> _movementFunction;
};


