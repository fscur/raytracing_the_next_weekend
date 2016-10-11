#include "sampler.h"
#include "../common/random.h"

vec3 sampler::randomPositionInUnitSphere()
{
    vec3 randomPosition;
    do
    {
        float x = random::next();
        float y = random::next();
        float z = random::next();

        randomPosition = 2.0f * vec3(x, y, z) - 1.0f;

    } while (dot(randomPosition, randomPosition) >= 1.0f);

    return randomPosition;
}

vec3 sampler::randomPositionInDisk()
{

    vec3 randomPosition;
    do
    {
        float x = random::next();
        float y = random::next();

        randomPosition = 2.0f * vec3(x, y, 0.0f) - vec3(1.0f, 1.0f, 0);

    } while (dot(randomPosition, randomPosition) >= 1.0);

    return randomPosition;
}
