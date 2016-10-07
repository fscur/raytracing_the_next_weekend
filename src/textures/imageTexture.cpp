#include "imageTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"

imageTexture::imageTexture(std::string fileName, const vec2& scale):
    _scale(scale)
{
    int comp;
    stbi_set_flip_vertically_on_load(true);
    _data = stbi_load(fileName.c_str(), &_width, &_height, &comp, 0);
}

inline vec3 imageTexture::fetch(const vec2 & uv, const vec3 point) const
{
    int i = uv.x * _width * _scale.x;
    int j = uv.y * _height * _scale.y - 0.001;

    i = i % _width;
    j = j % _height;

    if (i < 0)
        i = 0;

    if (j < 0)
        j = 0;

    if (i > _width - 1)
        i = _width - 1;

    if (j > _height - 1)
        j = _height - 1;

    float invD = 1.0f / 255.0f;

    float r = int(_data[j *_width * 3 + i * 3 + 0]) * invD;
    float g = int(_data[j *_width * 3 + i * 3 + 1]) * invD;
    float b = int(_data[j *_width * 3 + i * 3 + 2]) * invD;

    return vec3(r, g, b);
}
