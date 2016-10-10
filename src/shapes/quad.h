#pragma once

#include "shape.h"
#include "../math/rectangle.h"

class xy_quad :
    public shape 
{
public:
    xy_quad() 
    {}

    xy_quad(rectangle<float> rect, float z, material* material) :
        _x0(rect.x), 
        _x1(rect.w + rect.x), 
        _y0(rect.y), 
        _y1(rect.h + rect.y), 
        _z(z), 
        _material(material)
    {
    
    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const 
    {
        a = aabb(vec3(_x0, _y0, _z - 0.0001), vec3(_x1, _y1, _z + 0.0001));
        return true;
    }
    
private:
    material* _material;
    float _x0, _x1, _y0, _y1, _z;
};

class yz_quad :
    public shape
{
public:
    yz_quad()
    {}

    yz_quad(rectangle<float> rect, float x, material* material) :
        _y0(rect.x),
        _y1(rect.w + rect.x),
        _z0(rect.y),
        _z1(rect.h + rect.y),
        _x(x),
        _material(material)
    {

    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const
    {
        a = aabb(vec3(_x - 0.0001f, _y0, _z0), vec3(_x + 0.0001f, _y1, _z1));
        return true;
    }

private:
    material* _material;
    float _y0, _y1, _z0, _z1, _x;
};

class zx_quad :
    public shape
{
public:
    zx_quad()
    {}

    zx_quad(rectangle<float> rect, float y, material* material) :
        _z0(rect.x),
        _z1(rect.w + rect.x),
        _x0(rect.y),
        _x1(rect.h + rect.y),
        _y(y),
        _material(material)
    {

    }

    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;

    virtual bool createBoundingBox(float t0, float t1, aabb& a) const
    {
        a = aabb(vec3(_x0, _y - 0.0001f, _z0), vec3(_x1, _y + 0.0001f, _z1));
        return true;
    }

private:
    material* _material;
    float _z0, _z1, _x0, _x1, _y;
};

bool xy_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_z - r.origin.z) / r.direction.z;
    
    if (t < tMin || t > tMax)
        return false;

    float x = r.origin.x + t*r.direction.x;
    float y = r.origin.y + t*r.direction.y;

    if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
        return false;

    hit.uv = vec2((x - _x0) / (_x1 - _x0), (y - _y0) / (_y1 - _y0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(0.0f, 0.0f, 1.0f);

    return true;
}

bool yz_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_x - r.origin.x) / r.direction.x;

    if (t < tMin || t > tMax)
        return false;

    float y = r.origin.y + t*r.direction.y;
    float z = r.origin.z + t*r.direction.z;

    if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
        return false;

    hit.uv = vec2((y - _y0) / (_y1 - _y0), (z - _z0) / (_z1 - _z0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(1.0f, 0.0f, 0.0f);

    return true;
}

bool zx_quad::hit(const ray& r, float tMin, float tMax, intersection& hit) const
{
    float t = (_y - r.origin.y) / r.direction.y;

    if (t < tMin || t > tMax)
        return false;

    float z = r.origin.z + t*r.direction.z;
    float x = r.origin.x + t*r.direction.x;

    if (z < _z0 || z > _z1 || x < _x0 || x > _x1)
        return false;

    hit.uv = vec2((z - _z0) / (_z1 - _z0), (x - _x0) / (_x1 - _x0));
    hit.t = t;
    hit.material = _material;
    hit.point = r.pointAtParameter(t);
    hit.normal = vec3(0.0f, 1.0f, 0.0f);

    return true;
}