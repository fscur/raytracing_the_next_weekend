#pragma once
#include <vector>
#include "../math/ray.h"
#include "../math/intersection.h"
#include "../shapes/shape.h"
#include "camera.h"

class scene
{
public:
    static scene* createRandomScene(camera* camera);

public:
    scene(camera* camera);
    void addShape(shape* shape);
    bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const;

    camera* getCamera() const { return _camera; }

private:
    std::vector<shape*> _shapes;
    camera* _camera;
};


