#include "../common/sampler.h"
#include "camera.h"

camera::camera(float fov, float aspect, float aperture, float focusDistance)
{
    _lensRadius = aperture * 0.5f;
    _focusDistance = focusDistance;
    _theta = fov;
    _halfHeight = glm::tan(_theta * 0.5f);
    _halfWidth = aspect * _halfHeight;
    _lowerLeftCorner = vec3(-_halfWidth * _focusDistance, -_halfHeight * _focusDistance, -_focusDistance);
    _horizontal = vec3(2.0f * _halfWidth, 0.0f, 0.0f);
    _vertical = vec3(0.0f, 2.0f * _halfHeight, 0.0f);
    _origin = vec3(0.0f, 0.0f, 0.0f);
}

ray camera::castRay(vec2 uv)
{
    vec3 rd = _lensRadius * sampler::randomPositionInDisk();
    vec3 offset = _u * rd.x + _v * rd.y;
    return ray(
        _origin + offset,
        _lowerLeftCorner + uv.x * _horizontal + uv.y * _vertical - _origin - offset);
}

void camera::lookAt(vec3 from, vec3 at, vec3 up)
{
    _w = normalize(from - at);
    _u = normalize(cross(up, _w));
    _v = cross(_w, _u);
    _origin = from;

    vec3 pu = _halfWidth * _focusDistance * _u;
    vec3 pv = _halfHeight * _focusDistance * _v;
    vec3 pw = _focusDistance * _w;

    _lowerLeftCorner = _origin - pu - pv - pw;

    _horizontal = 2.0f * pu;
    _vertical = 2.0f * pv;
}
