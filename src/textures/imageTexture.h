#pragma once
#include "texture.h"

class imageTexture :
    public texture
{
public:
    imageTexture(std::string fileName, const vec2& scale = vec2(1.0f));
    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    int _width;
    int _height;
    vec2 _scale;
    byte* _data;
};