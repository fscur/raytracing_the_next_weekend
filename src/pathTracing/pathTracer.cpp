#include <iostream>
#include "../samplers/sampler.h"
#include "../common/random.h"
#include "../materials/material.h"
#include "../io/console.h"

#include "pathTracer.h"

#undef max

pathTracer::pathTracer(scene* scene) :
    MAX_FLOAT(std::numeric_limits<float>().max()),
    _running(false),
    _scene(scene),
    _camera(scene->getCamera())
{
}

pathTracer::~pathTracer()
{
}

vec3 pathTracer::li(const ray& r, int depth)
{
    intersection hit;
    bool anyHit = _scene->hit(r, 0.0001f, MAX_FLOAT, hit);

    if (anyHit)
    {
        ray scattered;
        vec3 attenuation;

        if (depth < 5 && hit.material->scatter(r, hit, attenuation, scattered))
            return attenuation * li(scattered, depth + 1);
        else
            return vec3(0.0f);
    }
    else
    {
        vec3 dir = normalize(r.direction);
        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

void pathTracer::run(const pathTracerRunInfo& info, pixelWriter* pixelWriter)
{
    _running = true;
    float issp = 1.0f / float(info.ssp);
    float iwidth = 1.0f / float(info.width);
    float iheight = 1.0f / float(info.height);
    
    int tileXEnd = info.tile.w + info.tile.x;
    int tileYEnd = info.tile.h + info.tile.y;

    for (int j = info.tile.y; j < tileYEnd; ++j)
    {
        float y = float(j);
        
        if (!_running)
            break;

        for (int i = info.tile.x; i < tileXEnd; ++i)
        {
            float x = float(i);
            vec3 color;
            for (int k = 0; k < info.ssp; ++k)
            {
                float u = (x + random::next()) * iwidth;
                float v = (y + random::next()) * iheight;
                const ray r = _camera->castRay(vec2(u, v), 0.0);
                color += li(r, 0);
            }
            color *= issp;

            pixelWriter->write(x, y, sqrt(color.x), sqrt(color.y), sqrt(color.z));
        }
    }
}

void pathTracer::cancel()
{
    _running = false;
}
