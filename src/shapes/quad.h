#pragma once

#include "shape.h"

class xy_quad : 
    public shape {
public:
    xy_quad() {}
    xy_quad(float _x0, float _x1, float _y0, float _y1, float _k, material *mat) : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};
    virtual bool hit(const ray& r, float t0, float t1, intersection& rec) const;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const {
        a = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
        return true;
    }
    material  *mp;
    float x0, x1, y0, y1, k;
};


bool xy_quad::hit(const ray& r, float t0, float t1, intersection& rec) const 
{
    float t = (k - r.origin.z) / r.direction.z;
    if (t < t0 || t > t1)
        return false;
    float x = r.origin.x + t*r.direction.x;
    float y = r.origin.y + t*r.direction.y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.uv = vec2((x - x0) / (x1 - x0), (y - y0) / (y1 - y0));
    rec.t = t;
    rec.material = mp;
    rec.point = r.pointAtParameter(t);
    rec.normal = vec3(0, 0, 1);
    return true;
}