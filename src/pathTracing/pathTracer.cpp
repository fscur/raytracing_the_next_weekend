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

void pathTracer::setScene(scene* scene)
{
    _scene = scene;
    _camera = scene->getCamera();
}

vec3 pathTracer::li(const ray& r, int depth)
{
    intersection hit;
    bool anyHit = _scene->hit(r, 0.001f, MAX_FLOAT, hit);

    if (anyHit)
    {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = hit.material->emitted(hit.uv, hit.point);

        if (depth < 50 && hit.material->scatter(r, hit, attenuation, scattered))
            return emitted + attenuation * li(scattered, depth+1);
        else
            return emitted;
    }
    else
    {
        return _scene->getBackground(r);
    }
}

void pathTracer::run(const pathTracerRunInfo& info, pixelWriter* pixelWriter)
{
    _running = true;
    float invSsp = 1.0f / float(info.ssp);
    float invWidth = 1.0f / float(info.width);
    float invHeight = 1.0f / float(info.height);
    
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
                float u = (x + random::next()) * invWidth;
                float v = (y + random::next()) * invHeight;
                const ray r = _camera->castRay(vec2(u, v));
                color += li(r, 0);
            }
            color *= invSsp;

            pixelWriter->write(x, y, sqrt(color.x), sqrt(color.y), sqrt(color.z));
        }
    }
}

void pathTracer::cancel()
{
    _running = false;
}
