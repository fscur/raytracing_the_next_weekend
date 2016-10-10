#pragma once
#include "shape.h"

class translate :
    public shape
{

public:
    translate(shape* p, const vec3& offset) :
        _shape(p),
        _offset(offset)
    {
    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const;

private:
    shape* _shape;
    vec3 _offset;
};

bool translate::hit(const ray& r, float tMin, float tMax, intersection& hit) const 
{
    ray translatedRay(r.origin - _offset, r.direction, r.time);

    if (_shape->hit(translatedRay, tMin, tMax, hit))
    {
        hit.point += _offset;
        return true;
    }
    else
        return false;
}

bool translate::createBoundingBox(float t0, float t1, aabb& a) const
{
    if (_shape->createBoundingBox(t0, t1, a)) 
    {
        a = aabb(a.min + _offset, a.max + _offset);
        return true;
    }
    else
        return false;
}