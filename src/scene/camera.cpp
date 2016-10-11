#include "../samplers/sampler.h"
#include "../common/random.h"
#include "camera.h"

camera::camera(
    float fov,
    float aspect,
    float aperture,
    float focusDistance,
    float shutterSpeed) :
    _fov(fov),
    _aspect(aspect),
    _aperture(aperture),
    _focusDistance(focusDistance),
    _shutterSpeed(shutterSpeed)
{
    _lensRadius = aperture * 0.5f;
    _halfHeight = glm::tan(fov * 0.5f);
    _halfWidth = aspect * _halfHeight;
    _lowerLeftCorner = vec3(-_halfWidth * _focusDistance, -_halfHeight * _focusDistance, -_focusDistance);
    _horizontal = vec3(2.0f * _halfWidth, 0.0f, 0.0f);
    _vertical = vec3(0.0f, 2.0f * _halfHeight, 0.0f);
    _position = vec3(0.0f, 0.0f, 0.0f);
}

ray camera::castRay(vec2 uv)
{
    vec3 randomPositionInLens = _lensRadius * sampler::randomPositionInDisk();
    vec3 offset = _u * randomPositionInLens.x + _v * randomPositionInLens.y;
    vec3 castOrigin = _position + offset;
    vec3 castDirection = _lowerLeftCorner + uv.x * _horizontal + uv.y * _vertical - _position - offset;
    float castTime = random::next() * _shutterSpeed;
    return ray(castOrigin, castDirection, castTime);
}

void camera::lookAt(vec3 eye, vec3 at, vec3 up)
{
    _w = normalize(eye - at);
    _u = normalize(cross(up, _w));
    _v = cross(_w, _u);
    _position = eye;

    vec3 pu = _halfWidth * _focusDistance * _u;
    vec3 pv = _halfHeight * _focusDistance * _v;
    vec3 pw = _focusDistance * _w;

    _lowerLeftCorner = _position - pu - pv - pw;

    _horizontal = 2.0f * pu;
    _vertical = 2.0f * pv;
}
