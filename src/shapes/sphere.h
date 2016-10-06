#pragma once

#include "shape.h"
#include "../materials/material.h"

class sphere :
    public shape
{
public:
    sphere(glm::vec3 center, float radius, material* mat);
    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;

public:
    glm::vec3 center;
    float radius;
    material* mat;
};


