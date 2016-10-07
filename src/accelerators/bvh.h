#pragma once
#include "../shapes/shape.h"

class bvh : 
    public shape
{
public:
    bvh() 
    {}

    bvh(std::vector<shape*>& shapes, float time0, float time1);

    virtual bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const override;
    virtual bool createBoundingBox(float t0, float t1, aabb& aabb) const override;

private:
    shape* _left;
    shape* _right;
    aabb _aabb;
};