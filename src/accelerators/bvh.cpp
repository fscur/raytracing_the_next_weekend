#include "bvh.h"
#include "../common/random.h"
#include <algorithm>
#include <iostream>

bool aabbXCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.x - rightAabb.min.x < 0.0);
}

bool aabbYCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.y - rightAabb.min.y < 0.0);
}

bool aabbZCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.z - rightAabb.min.z < 0.0);
}

bvh::bvh(std::vector<shape*>& shapes, float time0, float time1)
{
    int axis = int(3 * random::next());

    if (axis == 0)
        std::sort(shapes.begin(), shapes.end(), aabbXCompare);
    else if (axis == 1)
        std::sort(shapes.begin(), shapes.end(), aabbYCompare);
    else
        std::sort(shapes.begin(), shapes.end(), aabbZCompare);

    auto n = shapes.size();

    if (n == 1) 
    {
        _left = _right = shapes[0];
    }
    else if (n == 2) 
    {
        _left = shapes[0];
        _right = shapes[1];
    }
    else 
    {
        std::vector<shape*> leftShapes(shapes.begin(), shapes.begin() + n / 2);
        std::vector<shape*> rightShapes(shapes.begin() + n / 2, shapes.end());

        _left = new bvh(leftShapes, time0, time1);
        _right = new bvh(rightShapes, time0, time1);
    }

    aabb leftAabb;
    aabb rightAabb; 

    bool createdLeftAabb = _left->createBoundingBox(time0, time1, leftAabb);
    bool createdRightAabb = _right->createBoundingBox(time0, time1, rightAabb);

    if (!createdLeftAabb || !createdRightAabb)
        std::cerr << "no bounding box in bvh_node constructor\n";

    _aabb = aabb::getSurroundingAabb(leftAabb, rightAabb);
}

/*
bool bvh::aabbXCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.x - rightAabb.min.x < 0.0);
}

bool bvh::aabbYCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.y - rightAabb.min.y < 0.0);
}

bool bvh::aabbZCompare(shape* a, shape* b)
{
    aabb leftAabb;
    aabb rightAabb;

    if (!a->createBoundingBox(0, 0, leftAabb) || !b->createBoundingBox(0, 0, rightAabb))
        std::cerr << "no bounding box in bvh_node constructor\n";

    return (leftAabb.min.z - rightAabb.min.z < 0.0);
}
*/

bool bvh::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    if (_aabb.intersect(ray, tMin, tMax))
    {
        intersection leftHit;
        intersection rightHit;

        bool leftWasHit = _left->hit(ray, tMin, tMax, leftHit);
        bool rightWasHit = _right->hit(ray, tMin, tMax, rightHit);

        if (leftWasHit && rightWasHit)
            hit = (leftHit.t < rightHit.t) ? leftHit : rightHit;
        else if (leftWasHit)
            hit = leftHit;
        else if (rightWasHit)
            hit = rightHit;
        else
            return false;

        return true;
    }

    return false;
}

bool bvh::createBoundingBox(float t0, float t1, aabb & aabb) const
{
    aabb = _aabb;
    return true;
}
