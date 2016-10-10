#pragma once
#include "shape.h"

class rotateY : 
    public shape
{
public:
    rotateY(shape* shape, float angle);
    virtual bool hit(const ray& r, float tMin, float tMax, intersection& hit) const;
    virtual bool createBoundingBox(float t0, float t1, aabb& a) const 
    {
        a = _aabb; 
        return _hasBox;
    }

private:
    shape* _shape;
    float _sinTheta;
    float _cosTheta;
    bool _hasBox;
    aabb _aabb;
};

rotateY::rotateY(shape* shape, float angle) :
    _shape(shape) 
{
    _sinTheta = sin(angle);
    _cosTheta = cos(angle);
    _hasBox = _shape->createBoundingBox(0, 1, _aabb);

    auto maxFloat = std::numeric_limits<float>().max();
    auto minFloat = std::numeric_limits<float>().lowest();

    vec3 min(maxFloat, maxFloat, maxFloat);
    vec3 max(minFloat, minFloat, minFloat);

    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++) 
        {
            for (int k = 0; k < 2; k++) 
            {
                float x = i*_aabb.max.x + (1 - i)*_aabb.min.x;
                float y = j*_aabb.max.y + (1 - j)*_aabb.min.y;
                float z = k*_aabb.max.z + (1 - k)*_aabb.min.z;
                float newx = _cosTheta*x + _sinTheta*z;
                float newz = -_sinTheta*x + _cosTheta*z;
                vec3 tester(newx, y, newz);
                for (int c = 0; c < 3; c++)
                {
                    if (tester[c] > max[c])
                        max[c] = tester[c];
                    if (tester[c] < min[c])
                        min[c] = tester[c];
                }
            }
        }
    }
    _aabb = aabb(min, max);
}

bool rotateY::hit(const ray& r, float tMin, float tMax, intersection& hit) const 
{
    vec3 origin = r.origin;
    vec3 direction = r.direction;
    
    origin.x = _cosTheta * r.origin.x - _sinTheta * r.origin.z;
    origin.z = _sinTheta * r.origin.x +_cosTheta * r.origin.z;
    direction.x = _cosTheta * r.direction.x - _sinTheta * r.direction.z;
    direction.z = _sinTheta * r.direction.x + _cosTheta * r.direction.z;

    ray rotatedRay(origin, direction, r.time);

    if (_shape->hit(rotatedRay, tMin, tMax, hit))
    {
        vec3 p = hit.point;
        vec3 normal = hit.normal;
        
        p.x = _cosTheta * hit.point.x + _sinTheta * hit.point.z;
        p.z = -_sinTheta * hit.point.x + _cosTheta * hit.point.z;
        normal.x = _cosTheta * hit.normal.x + _sinTheta * hit.normal.z;
        normal.z = -_sinTheta * hit.normal.x + _cosTheta * hit.normal.z;

        hit.point = p;
        hit.normal = normal;

        return true;
    }
    else
        return false;
}