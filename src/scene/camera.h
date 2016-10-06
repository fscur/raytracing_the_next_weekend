#pragma once

#include "../math/ray.h"

class camera
{
public:
    camera(float fov, float aspect, float aperture, float focusDistance);
    void lookAt(vec3 from, vec3 at, vec3 up);
    ray castRay(vec2 uv);

private:
    float _theta;
    float _halfHeight;
    float _halfWidth;

    vec3 _origin;
    vec3 _lowerLeftCorner;
    vec3 _horizontal;
    vec3 _vertical;
    vec3 _u, _v, _w;
    float _focusDistance;
    float _lensRadius;
};


