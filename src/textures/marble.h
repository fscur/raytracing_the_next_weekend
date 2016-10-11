#pragma once
#include "texture.h"
#include "../math/perlin.h"

class marble :
    public texture
{
public:
    marble(vec3 scale, vec3 color) :
        _scale(scale),
        _color(color)
    {}

    virtual vec3 fetch(const vec2& uv, const vec3 point) const override
    {
        return _color * 0.5f * (1.0f + sin(_scale.x*point.x + 5.0f * _perlin.turb(_scale.x * point)));
        //vec3 c0 = _color * 0.5f * (1.0f + sin(_scale.x*point.x + 10 * _perlin.turb(point)));
    }

private:
    vec3 _scale;
    vec3 _color;
    perlin _perlin;
};