#pragma once
#include <vector>
#include "../math/ray.h"
#include "../math/intersection.h"
#include "../shapes/shape.h"
#include "../accelerators/bvh.h"
#include "camera.h"

class scene
{
public:
    static scene* scene1();
    static scene* scene2();
    static scene* scene3();
    static scene* earthScene();

public:
    scene(camera* camera);
    void addShape(shape* shape);
    void buildBvh();
    bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const;

    camera* getCamera() const { return _camera; }

private:
    std::vector<shape*> _shapes;
    bvh _bvh;
    camera* _camera;
};


