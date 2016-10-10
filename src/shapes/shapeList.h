#pragma once
#include "shape.h"
#include <vector>

class shapeList
{
public:
    shapeList() {}
    
    void add(shape* shape)
    {
        _shapes.push_back(shape);

    }

    bool hit(const ray& r, float tMin, float tMax, intersection& hit) const
    {
        intersection tempRecord;
        bool hitAnything = false;
        double closestHit = tMax;
        auto listCount = _shapes.size();

        for (int i = 0; i < listCount; ++i)
        {
            if (_shapes[i]->hit(r, tMin, closestHit, tempRecord))
            {
                hitAnything = true;
                closestHit = tempRecord.t;
                hit = tempRecord;
            }
        }

        return hitAnything;
    }

private:
    std::vector<shape*> _shapes;
};