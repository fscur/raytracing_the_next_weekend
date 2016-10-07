#include "solidColor.h"

solidColor* solidColor::red = new solidColor(vec3(0.97f, 0.0f, 0.0f));
solidColor* solidColor::green = new solidColor(vec3(0.0f, 0.97f, 0.0f));
solidColor* solidColor::blue = new solidColor(vec3(0.0f, 0.0f, 0.97f));
solidColor* solidColor::black = new solidColor(vec3(0.03f, 0.03f, 0.03f));
solidColor* solidColor::white = new solidColor(vec3(0.97f, 0.97f, 0.97f));


solidColor::solidColor(const vec3 & color) :
    _color(color)
{
}

vec3 solidColor::fetch(const vec2 & uv, const vec3 point) const
{
    return _color;
}
