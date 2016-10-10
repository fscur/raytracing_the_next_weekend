#pragma once

#include "shape.h"

class flipNormals :
    public shape
{
public:
    flipNormals(shape* shape) :
        _shape(shape)
    {}

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const
    {
        if (_shape->hit(r, tMin, tMax, hit))
        {
            hit.normal = -hit.normal;
            return true;
        }

        return false;
    }

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const
    {
        return _shape->createBoundingBox(t0 ,t1, a);
    }

private:
    shape* _shape;
};