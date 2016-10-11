#pragma once

#include "../math/ray.h"

class camera
{
public:
    camera(
        float fov, 
        float aspect, 
        float aperture, 
        float focusDistance, 
        float shutterSpeed);

    void lookAt(vec3 eye, vec3 at, vec3 up);
    ray castRay(vec2 uv);

private:
    float _fov;
    float _aspect;
    float _aperture;
    float _shutterSpeed;
    float _focusDistance;
    float _lensRadius;
    float _halfHeight;
    float _halfWidth;

    vec3 _position;
    vec3 _lowerLeftCorner;
    vec3 _horizontal;
    vec3 _vertical;
    vec3 _u, _v, _w;
};


