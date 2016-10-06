#pragma once
#include "../common/types.h"

class vMath
{
public:
    static float schlick(float cosine, float indexOfRefraction)
    {
        float r0 = (1.0f - indexOfRefraction) / (1.0f + indexOfRefraction);
        r0 *= r0;
        float p = 1.0f - cosine;
        return r0 + (1.0f - r0) * (p * p * p * p * p);
    }

    static bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
    {
        vec3 uv = normalize(v);
        float dt = dot(uv, n);
        float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
        if (discriminant > 0.0f)
        {
            refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
            return true;
        } else
            return false;
    }

    static vec3 reflect(const vec3& v, const vec3& n)
    {
        return v - 2.0f * dot(v, n) * n;
    }
};
