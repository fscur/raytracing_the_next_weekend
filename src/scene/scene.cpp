#include "../common/random.h"
#include "../shapes/sphere.h"
#include "../shapes/movingSphere.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "../materials/emissive.h"
#include "../textures/solidColor.h" 
#include "../textures/checker.h"
#include "../textures/noise.h"
#include "../textures/marble.h"
#include "../textures/imageTexture.h"
#include "../shapes/quad.h"
#include "scene.h"

scene* scene::scene1()
{
    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam);
    world->addShape(
        new sphere(
            vec3(+0.0f, -1000.f, 0.0f),
            1000.0f,
            new lambertian(new solidColor(vec3(0.5f, 0.5f, 0.5f)))));

    int w = 3;

    for (int a = -w; a < w; a++)
    {
        for (int b = -w; b < w; b++)
        {
            float choose_mat = random::next();

            vec3 center(a + 0.9f * random::next(), 0.2f, b + 0.9f * random::next());

            if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.5f)
            {
                if (choose_mat < 0.3)
                {
                    auto color = vec3(
                        random::next() * random::next(),
                        random::next() * random::next(),
                        random::next() * random::next());

                    std::function<vec3(vec3, float, float)> movementFunc;

                    movementFunc = [=](vec3 p0, float t, float speed)
                    {
                        auto p1 = p0 + vec3(0.0f, random::next() * 0.5f, 0.0f);
                        return p0 + (t / speed) * (p1 - p0);
                    };

                    world->addShape(
                        new movingSphere(
                            center,
                            0.2f,
                            1.0f,
                            new lambertian(new solidColor(color)),
                            movementFunc));
                }
                else if (choose_mat < 0.7)
                {
                    auto color = vec3(
                        random::next() * random::next(),
                        random::next() * random::next(),
                        random::next() * random::next());

                    world->addShape(new sphere(center, 0.2f, new lambertian(new solidColor(color))));

                }
                else if (choose_mat < 0.85)
                {
                    auto color = vec3(
                        0.5f * (1.0f + random::next()),
                        0.5f * (1.0f + random::next()),
                        0.5f * (1.0f + random::next()));

                    world->addShape(new sphere(center, 0.2f, new metal(new solidColor(color), 0.5f * random::next())));
                }
                else
                {
                    world->addShape(new sphere(center, 0.2, new dielectric(1.5f)));
                }
            }
        }
    }

    world->addShape(new sphere(vec3(-4, 1, 0), 1.0, new metal(new solidColor(vec3(0.5, 0.4, 0.7)), 0.0)));
    world->addShape(new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5)));
    world->addShape(new sphere(vec3(4, 1, 0), 1.0, new lambertian(new solidColor(vec3(0.4, 0.2, 0.1)))));

    /*int w = 100;

    for (int i = -w; i < w; ++i)
    {
        for (int j = -w; j < w; ++j)
        {
            vec3 center(i + 1.0f * random::next(), 0.2, j + 1.0 * random::next());
            world->addShape(new sphere(center, 0.2f, new lambertian(vec3(random::next(), random::next(), random::next()))));
        }
    }*/

    /* world->addShape(new sphere(vec3(+0.0f, -1000.f, 0.0f), 1000.0f, new lambertian(vec3(0.5f, 0.5f, 0.5f))));
     world->addShape(new sphere(vec3(-3.0f, 1.0f, -3.0f), 1.0f, new metal(vec3(0.5f, 0.4f, 0.7f), 0.0f)));
     world->addShape(new sphere(vec3(-3.0f, 1.0f, +3.0f), 1.0f, new dielectric(1.5f)));
     world->addShape(new sphere(vec3(+3.0f, 1.0f, -3.0f), 1.0f, new dielectric(1.5f)));
     world->addShape(new sphere(vec3(+3.0f, 1.0f, +3.0f), 1.0f, new lambertian(vec3(0.9f, 0.1f, 0.0f))));
 */
    world->buildBvh();

    return world;
}

scene* scene::scene2()
{
    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam);

    auto checkerTexture = new checker(solidColor::white, solidColor::black);
    auto noiseTexture = new noise(vec3(5.0f));
    auto blueMarbleTexture = new marble(vec3(5.0f), vec3(0.5, 0.6, 0.9));

    auto position = vec3(+0.0f, -1000.f, 0.0f);
    world->addShape(new sphere(position, 1000.0f, new lambertian(blueMarbleTexture)));

    /*int w = 3;

    for (int i = -w; i < w; ++i)
    {
        for (int j = -w; j < w; ++j)
        {
            vec3 center(i + 1.0f * random::next(), 0.2, j + 1.0 * random::next());
            world->addShape(new sphere(center, 0.2f, new lambertian(new solidColor(vec3(
                0.6 * random::next(), 0.3 * random::next(), 0.6 * random::next())))));
        }
    }*/

    world->addShape(new sphere(vec3(-3.0f, 1.0f, -3.0f), 1.0f, new metal(new solidColor(vec3(0.2, 0.3, 0.5)), 0.0f)));
    world->addShape(new sphere(vec3(-3.0f, 1.0f, +3.0f), 1.0f, new dielectric(2.4f)));
    world->addShape(new sphere(vec3(+3.0f, 1.0f, -3.0f), 1.0f, new dielectric(1.5f)));
    world->addShape(new sphere(vec3(+3.0f, 1.0f, +3.0f), 1.0f, new lambertian(solidColor::red)));

    world->buildBvh();

    return world;
}

scene* scene::scene3()
{
    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam);

    auto checkerTexture = new checker(solidColor::white, solidColor::red);
    world->addShape(new sphere(vec3(0.0f, -10.0f, 0.0f), 10.0f, new metal(new solidColor(vec3(0.2, 0.5, 0.3)), 0.05f)));
    world->addShape(new sphere(vec3(0.0f, 10.0f, 0.0f), 10.0f, new lambertian(checkerTexture)));

    world->buildBvh();

    return world;
}

scene* scene::earthScene()
{
    vec3 eye(0.0f, 0.5f, 2.0f);
    vec3 at(0.0f, 1.2, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam);

    auto earthTexture = new imageTexture("earthmap.jpg");
    auto earthPosition = vec3(0.0f, 0.0f, 0.0f);
    world->addShape(new sphere(earthPosition, 1.0f, new lambertian(earthTexture)));

    auto moonTexture = new imageTexture("moonmap.png");
    auto moonPosition = vec3(1.9f, 4.2f, -8.0f);
    world->addShape(new sphere(moonPosition, 0.15f, new emissive(moonTexture, 10.0f)));

    world->buildBvh();

    return world;
}

scene* scene::quadLightScene()
{
    vec3 eye(12.0f, 5.0f, 4.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam);
    world->addShape(
        new sphere(
            vec3(+0.0f, -1000.f, 0.0f),
            1000.0f,
            new lambertian(new solidColor(vec3(0.5f, 0.5f, 0.5f)))));

    world->addShape(new sphere(vec3(+3.0f, 1.0f, +3.0f), 1.0f, new lambertian(solidColor::red)));
    world->addShape(new xy_quad(0, 4, 0, 4, 0, new emissive(solidColor::white, 1.0f)));
    world->addShape(new sphere(vec3(0.0f, 1.0f, +3.0f), 1.0f, new emissive(solidColor::blue, 1.0f)));

    world->buildBvh();

    return world;
}

scene::scene(camera* camera) :
    _camera(camera)
{
}

bool scene::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    if (_shapes.size() < 10)
    {
        intersection tempRecord;
        bool hitAnything = false;
        double closestHit = tMax;
        auto listCount = _shapes.size();

        for (int i = 0; i < listCount; ++i)
        {
            if (_shapes[i]->hit(ray, tMin, closestHit, tempRecord))
            {
                hitAnything = true;
                closestHit = tempRecord.t;
                hit = tempRecord;
            }
        }

        return hitAnything;
    }

    return _bvh.hit(ray, tMin, tMax, hit);
}

void scene::addShape(shape* shape)
{
    _shapes.push_back(shape);
}

void scene::buildBvh()
{
    _bvh = bvh(_shapes, 0.0f, 1.0f);
}
