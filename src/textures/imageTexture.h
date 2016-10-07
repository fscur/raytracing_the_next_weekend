#pragma once
#include "texture.h"

class imageTexture :
    public texture
{
public:
    imageTexture(std::string fileName);
    virtual vec3 fetch(const vec2& uv, const vec3 point) const override;

private:
    int _width;
    int _height;
    byte* _data;
};