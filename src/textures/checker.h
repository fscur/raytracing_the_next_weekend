#pragma once
#include "texture.h"

class checker :
    public texture
{
public:
    checker(texture* odd, texture* even) :
        _odd(odd),
        _even(even)
    {}

    virtual vec3 fetch(const vec2& uv, const vec3 point) const override
    {
        float sines = sin(10 * point.x) * sin(10 * point.y) * sin(10 * point.z);
        return sines < 0 ? _odd->fetch(uv, point) : _even->fetch(uv, point);
    }

private:
    texture* _odd;
    texture* _even;
};
