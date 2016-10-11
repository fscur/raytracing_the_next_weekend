#pragma once
#include <vector>
#include <functional>
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
    static scene* quadLightScene();
    static scene* cornelBoxScene();
    static scene* cornelBoxSmokeScene();
    static scene* finalScene();
    static scene* poolScene();

public:
    scene(camera* camera, std::function<vec3(const ray&)> getBackgroundFunction);
    void addShape(shape* shape);
    void buildBvh();
    bool hit(const ray& ray, float tMin, float tMax, intersection& hit) const;

    camera* getCamera() const { return _camera; }
    vec3 getBackground(const ray& ray) const { return _getBackgroundFunction(ray); }

private:
    std::vector<shape*> _shapes;
    bvh _bvh;
    camera* _camera;
    std::function<vec3(const ray&)> _getBackgroundFunction;
};


