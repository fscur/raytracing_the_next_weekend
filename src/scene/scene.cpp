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
#include "../shapes/flipNormals.h"
#include "../shapes/box.h"
#include "../shapes/translate.h"
#include "../shapes/rotateY.h"
#include "../shapes/constantMedium.h"

#include "scene.h"

scene* scene::scene1()
{
    auto backGroundFunction = [](const ray& ray)
    {
        vec3 dir = normalize(ray.direction);
        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.2f, 0.5f, 0.7f);
    };

    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);
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
    auto backGroundFunction = [](const ray& ray)
    {
        vec3 dir = normalize(ray.direction);
        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.2f, 0.5f, 0.7f);
    };

    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

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
    auto backGroundFunction = [](const ray& ray)
    {
        vec3 dir = normalize(ray.direction);
        float t = 0.5f * (dir.y + 1.0f);
        return (1.0f - t) * vec3(1.0f) + t * vec3(0.2f, 0.5f, 0.7f);
    };

    vec3 eye(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    auto checkerTexture = new checker(solidColor::white, solidColor::red);
    world->addShape(new sphere(vec3(0.0f, -10.0f, 0.0f), 10.0f, new metal(new solidColor(vec3(0.2, 0.5, 0.3)), 0.05f)));
    world->addShape(new sphere(vec3(0.0f, 10.0f, 0.0f), 10.0f, new lambertian(checkerTexture)));

    world->buildBvh();

    return world;
}

scene* scene::earthScene()
{
    auto backGroundFunction = [](const ray& ray) 
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(0.0f, 0.5f, 2.0f);
    vec3 at(0.0f, 1.2, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    auto earthTexture = new imageTexture("earthmap.jpg");
    auto earthPosition = vec3(0.0f, 0.0f, 0.0f);
    world->addShape(new sphere(earthPosition, 1.0f, new lambertian(earthTexture)));

    auto moonTexture = new imageTexture("moonmap.png");
    auto moonPosition = vec3(1.9f, 4.2f, -8.0f);
    world->addShape(new sphere(moonPosition, 0.15f, new emissive(moonTexture)));

    world->buildBvh();

    return world;
}

scene* scene::quadLightScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(20.0f, 15.0f, 20.0f);
    vec3 at(0.0f, 0.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);
    world->addShape(
        new sphere(
            vec3(+0.0f, -1000.f, 0.0f),
            1000.0f,
            new lambertian(new solidColor(vec3(0.5f, 0.5f, 0.5f)))));

    world->addShape(new xy_quad(rectangle<float>(-5.0f, 0.0f, 10.0f, 5.0f), -5.0f, new emissive(new solidColor(vec3(1.0f, 0.8f, 0.65f)))));
    world->addShape(new yz_quad(rectangle<float>(0.0f, -5.0f, 5.0f, 10.0f), -5.0f, new emissive(new solidColor(vec3(1.0f, 0.8f, 0.65f)))));
    world->addShape(new sphere(vec3(0.0f, 1.0f, +5.0f), 1.0f, new metal(solidColor::white, 0.1f)));
    world->addShape(new sphere(vec3(3.0f, 1.0f, +3.0f), 1.0f, new dielectric(1.5f)));
    world->addShape(new sphere(vec3(0.0f, 1.0f, +0.0f), 1.0f, new lambertian(solidColor::red)));

    world->buildBvh();

    return world;
}

scene* scene::cornelBoxScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(278.0f, 278.0f, -800.0f);
    vec3 at(278.0f, 278.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    material* red = new lambertian(new solidColor(vec3(0.65, 0.05, 0.05)));
    material* white = new lambertian(new solidColor(vec3(0.73, 0.73, 0.73)));
    material* green = new lambertian(new solidColor(vec3(0.12, 0.45, 0.15)));
    material* light = new emissive(new solidColor(vec3(15, 15, 15)));

    auto greenWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, green);
    auto redWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, red);
    auto ceilingLight = new zx_quad(rectangle<float>(213.0f, 227.0f, 130.0f, 105.0f), 554.0f, light);
    auto ceiling = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, white);
    auto floor = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, white);
    auto backWall = new xy_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, white);

    world->addShape(new flipNormals(greenWall));
    world->addShape(redWall);
    world->addShape(new flipNormals(ceiling));
    world->addShape(ceilingLight);
    world->addShape(floor);
    world->addShape(new flipNormals(backWall));

    auto shortBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 165.0f, 165.0f), white);
    auto tallBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 330.0f, 165.0f), white);

    world->addShape(new translate(new rotateY(shortBox, -18.0f * (glm::pi<float>()/180.0f)), vec3(130.0f, 0.0f, 65.0f)));
    world->addShape(new translate(new rotateY(tallBox, 15.0f * (glm::pi<float>() / 180.0f)), vec3(265.0f, 0.0f, 295.0f)));

    world->buildBvh();

    return world;
}

scene* scene::cornelBoxSmokeScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(278.0f, 278.0f, -800.0f);
    vec3 at(278.0f, 278.0, 0.0f);
    float focusDistance = length(eye - at);
    float aperture = 0.0f;
    float fov = 40.0f * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    material* red = new lambertian(new solidColor(vec3(0.65, 0.05, 0.05)));
    material* white = new lambertian(new solidColor(vec3(0.73, 0.73, 0.73)));
    material* green = new lambertian(new solidColor(vec3(0.12, 0.45, 0.15)));
    material* light = new emissive(new solidColor(vec3(1, 1, 1)));

    auto greenWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, green);
    auto redWall = new yz_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, red);
    auto ceilingLight = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, light);
    auto floor = new zx_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 0.0f, white);
    auto backWall = new xy_quad(rectangle<float>(0.0f, 0.0f, 555.0f, 555.0f), 555.0f, white);

    world->addShape(new flipNormals(greenWall));
    world->addShape(redWall);
    world->addShape(new flipNormals(ceilingLight));
    world->addShape(floor);
    world->addShape(new flipNormals(backWall));

    auto shortBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 165.0f, 165.0f), white);
    auto tallBox = new box(vec3(0.0f, 0.0f, 0.0f), vec3(165.0f, 330.0f, 165.0f), white);

    auto whiteSmokeBox = 
        new constantMedium(
            new translate(
                new rotateY(shortBox, -18.0f * (glm::pi<float>() / 180.0f)), 
                vec3(130.0f, 0.0f, 65.0f)), 
            0.01f, 
            solidColor::white);

    auto darkSmokeBox =
        new constantMedium(
            new translate(
                new rotateY(tallBox, 15.0f * (glm::pi<float>() / 180.0f)),
                vec3(265.0f, 0.0f, 295.0f)),
            0.01f,
            solidColor::black);

    world->addShape(whiteSmokeBox);
    world->addShape(darkSmokeBox);

    world->buildBvh();

    return world;
}

scene* scene::finalScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0, 1.0f, 5.0f) / 255.999f;
    };

    vec3 eye(478, 278, -600);
    vec3 at(278, 278, 0);
    float focusDistance = 10.0;
    float aperture = 0.0;
    float fov = 40 * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    material* white = new lambertian(new solidColor(vec3(0.73, 0.73, 0.73)));
    material* ground = new lambertian(new solidColor(vec3(0.48, 0.83, 0.53)));

    int nb = 20;
    int b = 0;

    for (int i = 0; i < nb; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            float w = 100;
            float x0 = -1000 + i*w;
            float z0 = -1000 + j*w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100 * (random::next() + 0.01);
            float z1 = z0 + w;
            world->addShape(new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground));
        }
    }

    material* light = new emissive(new solidColor(vec3(7, 7, 7)));

    world->addShape(new zx_quad(rectangle<float>(147, 123, 265, 300), 554, light));

    std::function<vec3(vec3, float, float)> movementFunc;

    movementFunc = [=](vec3 p0, float t, float speed)
    {
        auto p1 = p0 + vec3(30.0f, 0.0, 0.0f);
        return p0 + (t / speed) * (p1 - p0);
    };

    vec3 center(400, 400, 200);
    world->addShape(new movingSphere(center, 50, 1.0f, new lambertian(new solidColor(vec3(0.7, 0.3, 0.1))), movementFunc));
    world->addShape(new sphere(vec3(260, 150, 45), 50, new dielectric(1.5)));
    world->addShape(new sphere(vec3(0, 150, 145), 50, new metal(new solidColor(vec3(0.8, 0.8, 0.9)), 10.0)));

    shape* boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    world->addShape(boundary);
    world->addShape(new constantMedium(boundary, 0.2, new solidColor(vec3(0.2, 0.4, 0.9))));

    boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    world->addShape(new constantMedium(boundary, 0.0001, new solidColor(vec3(1.0, 1.0, 1.0))));

    auto earthTexture = new imageTexture("earthmap.jpg");
    material* earthMaterial = new lambertian(earthTexture);
    world->addShape(new sphere(vec3(400, 200, 400), 100, earthMaterial));

    texture* marbleMaterial = new marble(vec3(0.1f), vec3(1.0f));
    world->addShape(new sphere(vec3(220, 280, 300), 80, new lambertian(marbleMaterial)));


    int ns = 1000;
    for (int j = 0; j < ns; j++)
    {
        world->addShape(new translate(new rotateY(new sphere(vec3(165 * random::next(), 165 * random::next(), 165 * random::next()), 10, white), 15.0f), vec3(-100, 270, 395)));
    }

    world->buildBvh();
    return world;
}

scene* scene::poolScene()
{
    auto backGroundFunction = [](const ray& ray)
    {
        return vec3(0.0f, 1.0f, 10.0f) / 255.999f;
    };

    vec3 eye(-4.0, 4.5, 12.17);
    vec3 at(0, 2.5, 0);
    float focusDistance = glm::length(eye-at);
    float aperture = 0.4;
    float fov = 45 * (glm::pi<float>() / 180.0f);

    auto cam = new camera(fov, 1.7778f, aperture, focusDistance, 1.0);
    cam->lookAt(eye, at, vec3(0.0f, 1.0f, 0.0f));

    scene* world = new scene(cam, backGroundFunction);

    material* white = new lambertian(new solidColor(vec3(0.73, 0.73, 0.73)));
    material* ground = new lambertian(new solidColor(vec3(0.05f, (81.0f/255.999f), 0.05f)));
    world->addShape(new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, ground));

    material* light = new emissive(new solidColor(vec3(12, 12, 12)));
    world->addShape(new zx_quad(rectangle<float>(-2.75, -2.75, 1.5, 1.5), 7, light));
    world->addShape(new box(vec3(-3, 7.01, -3), vec3(-1, 7.5, -1), new lambertian(solidColor::white)));

    world->addShape(new zx_quad(rectangle<float>(+3.25, -2.75, 1.5, 1.5), 7, light));
    world->addShape(new box(vec3(-3, 7.01, +3), vec3(-1, 7.5, 5), new lambertian(solidColor::white)));

    world->addShape(new zx_quad(rectangle<float>(+3.25, +3.25, 1.5, 1.5), 7, light));
    world->addShape(new box(vec3(+3, 7.01, +3), vec3(5, 7.5, 5), new lambertian(solidColor::white)));

    world->addShape(new zx_quad(rectangle<float>(-2.75, +3.25, 1.5, 1.5), 7, light));
    world->addShape(new box(vec3(+3, 7.01, -3), vec3(5, 7.5, -1), new lambertian(solidColor::white)));
    
    auto threeTexture = new imageTexture("three.png");
    world->addShape(new rotateY(new sphere(vec3(0.0f, 1.0f, 0.0f), 0.95f, new lambertian(threeTexture)), 0.3f));
    world->addShape(new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5f)));

    auto eightTexture = new imageTexture("eight.png");
    world->addShape(new translate(new rotateY(new sphere(vec3(0.0), 0.95f, new lambertian(eightTexture)), -0.1f), vec3(-2.5f, 1.0f, 0.3f)));
    world->addShape(new sphere(vec3(-2.5f, 1.0f, 0.3f), 1.0f, new dielectric(1.5f)));

    std::function<vec3(vec3, float, float)> movementFunc;

    movementFunc = [=](vec3 p0, float t, float speed)
    {
        auto p1 = p0 + vec3(0.5f * random::next(), 0.0, 0.0f);
        return p0 + (t / speed) * (p1 - p0);
    };

    auto oneTexture = new imageTexture("one.png");
    world->addShape(new movingSphere(vec3(2.2, 1.0, 1.4), 0.95f, 0.5, new lambertian(oneTexture), movementFunc));
    world->addShape(new movingSphere(vec3(2.2, 1.0, 1.4), 1.0f, 0.5, new dielectric(1.5f), movementFunc));
    
    world->addShape(new sphere(vec3(1.4142f, 1.0f, -1.4142f), 0.95f, new lambertian(solidColor::white)));
    world->addShape(new sphere(vec3(1.4142f, 1.0f, -1.4142f), 1.0f, new dielectric(1.5f)));

    auto boundary = new sphere(vec3(0, 0, 0), 50, new dielectric(1.5));
    world->addShape(new constantMedium(boundary, 0.005, new solidColor(vec3(1.0, 1.0, 1.0))));

    world->buildBvh();
    return world;
}

scene::scene(camera* camera, std::function<vec3(const ray&)> getBackgroundFunction) :
    _camera(camera),
    _getBackgroundFunction(getBackgroundFunction)
{
}

bool scene::hit(const ray& ray, float tMin, float tMax, intersection& hit) const
{
    /*if (_shapes.size() < 10)
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
    }*/

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
