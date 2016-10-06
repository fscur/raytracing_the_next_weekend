#include "../common/random.h"
#include "../shapes/sphere.h"
#include "../materials/lambertian.h"
#include "../materials/metal.h"
#include "../materials/dielectric.h"
#include "scene.h"

scene* scene::createRandomScene(camera* camera)
{
    scene* world = new scene(camera);

    world->addShape(new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5))));

    for (int a = -3; a < 3; a++)
    {
        for (int b = -3; b < 3; b++)
        {
            float choose_mat = random::next();

            vec3 center(a + 0.9 * random::next(), 0.2, b + 0.9 * random::next());

            if ((center - vec3(4, 0.2, 0)).length() > 0.5)
            {
                if (choose_mat < 0.7)
                {  // diffuse
                    auto color = vec3(
                        random::next() * random::next(),
                        random::next() * random::next(),
                        random::next() * random::next());

                    world->addShape(new sphere(center, 0.2f, new lambertian(color)));

                }
                else if (choose_mat < 0.85)
                { // metal
                    auto color = vec3(
                        0.5 * (1 + random::next()),
                        0.5 * (1 + random::next()),
                        0.5 * (1 + random::next()));

                    world->addShape(new sphere(center, 0.2f, new metal(color, 0.5f * random::next())));
                }
                else
                {
                    world->addShape(new sphere(center, 0.2, new dielectric(1.5f)));
                }
            }
        }
    }

    world->addShape(new sphere(vec3(-4, 1, 0), 1.0, new metal(vec3(0.5, 0.4, 0.7), 0.0)));
    world->addShape(new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5)));
    world->addShape(new sphere(vec3(4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1))));

    return world;
}

scene::scene(camera* camera) : 
    _camera(camera)
{
}

bool scene::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
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

void scene::addShape(shape* shape)
{
    _shapes.push_back(shape);
}
