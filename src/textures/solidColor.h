#pragma once
#include "texture.h"

class solidColor :
    public texture
{
public:
    static solidColor* red;
    static solidColor* green;
    static solidColor* blue;
    static solidColor* black;
    static solidColor* white;

public:
    solidColor(const vec3& color) :
        _color(color)
    {}

    virtual vec3 fetch(const vec2& uv, const vec3 point) const override
    {
        return _color;
    }

private:
    vec3 _color;
};