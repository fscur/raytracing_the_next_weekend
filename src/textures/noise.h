#pragma once
#include "texture.h"
#include "../math/perlin.h"

class noise :
    public texture
{
public:
    noise(vec3 scale) :
        _scale(scale)
    {}

    virtual vec3 fetch(const vec2& uv, const vec3 point) const override
    {
        return vec3(1.0f) * _perlin.noise(_scale*point);
    }
private:
    vec3 _scale;
    perlin _perlin;
};