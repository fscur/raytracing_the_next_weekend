//#pragma once
//#include "../common/types.h"
//#include "../common/random.h"
//
//
//
//class perlin
//{
//public:
//    static float trilinearInterpolation(float c[2][2][2], float u, float v, float w)
//    {
//        float accum = 0;
//        for (int i = 0; i < 2; ++i)
//            for (int j = 0; j < 2; ++j)
//                for (int k = 0; k < 2; ++k)
//                    accum +=
//                    (i * u + (1 - i) * (1 - u)) *
//                    (j * v + (1 - j) * (1 - v)) *
//                    (k * w + (1 - k) * (1 - w)) * c[i][j][k];
//
//        return accum;
//    }
//
//    static float trilinearVectorInterpolation(vec3 c[2][2][2], float u, float v, float w)
//    {
//        float uu = u*u * (3 - 2 * u);
//        float vv = v*v * (3 - 2 * v);
//        float ww = w*w * (3 - 2 * w);
//        float accum = 0;
//
//        for (int i = 0; i < 2; ++i)
//            for (int j = 0; j < 2; ++j)
//                for (int k = 0; k < 2; ++k)
//                {
//                    vec3 weight(u - i, v - j, w - k);
//
//                    accum +=
//                    (i * uu + (1 - i) * (1 - uu)) *
//                    (j * vv + (1 - j) * (1 - vv)) *
//                    (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight);
//                }
//
//        return accum;
//    }
//
//    static float noise(const vec3& point)
//    {
//        float u = point.x - floor(point.x);
//        float v = point.y - floor(point.y);
//        float w = point.z - floor(point.z);
//
//        int i = floor(point.x);
//        int j = floor(point.y);
//        int k = floor(point.z);
//
//        vec3 c[2][2][2];
//
//        for (int di = 0; di < 2; ++di)
//            for (int dj = 0; dj < 2; ++dj)
//                for (int dk = 0; dk < 2; ++dk)
//                {
//                    c[di][dj][dk] = 
//                        ranvec[
//                            permX[(i + di) & 255] ^ 
//                            permY[(j + dj) & 255] ^ 
//                            permZ[(k + dk) & 255]];
//                    
//                }
//
//        return trilinearVectorInterpolation(c, u, v, w);
//    }
//
//    static float turbulence(const vec3& p, int depth = 7)
//    {
//        float accum = 0;
//        vec3 temp_p = p;
//        float weight = 1.0;
//        for (int i = 0; i < depth; i++) {
//            accum += weight*noise(temp_p);
//            weight *= 0.5;
//            temp_p *= 2;
//        }
//        return fabs(accum);
//    }
//
//    static vec3* generate()
//    {
//        vec3* p = new vec3[256];
//        for (int i = 0; i < 256; ++i)
//        {
//            auto dir = vec3(
//                -1.0f + 2.0f * random::next(),
//                -1.0f + 2.0f * random::next(),
//                -1.0f + 2.0f * random::next());
//
//            p[i] = normalize(dir);
//        }
//
//        return p;
//    }
//
//    static void permute(int* p, int n)
//    {
//        for (int i = n - 1; i > 0; --i)
//        {
//            int target = int(random::next()*(i + 1));
//            int temp = p[i];
//            p[i] = p[target];
//            p[target] = temp;
//        }
//    }
//
//    static int* generatePerm()
//    {
//        int* p = new int[256];
//        for (int i = 0; i < 256; ++i)
//            p[i] = i;
//
//        permute(p, 256);
//        return p;
//    }
//
//public:
//    static vec3* ranvec;
//    static int* permX;
//    static int* permY;
//    static int* permZ;
//
//};

#ifndef PERLINH
#define PERLINH

#include "../common/types.h"
#include "../common/random.h"

inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w) {
    float uu = u*u*(3 - 2 * u);
    float vv = v*v*(3 - 2 * v);
    float ww = w*w*(3 - 2 * w);
    float accum = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++) {
                vec3 weight_v(u - i, v - j, w - k);
                accum += (i*uu + (1 - i)*(1 - uu))*
                    (j*vv + (1 - j)*(1 - vv))*
                    (k*ww + (1 - k)*(1 - ww))*dot(c[i][j][k], weight_v);
            }
    return accum;
}

class perlin {
public:
    float noise(const vec3& p) const {
        float u = p.x - floor(p.x);
        float v = p.y - floor(p.y);
        float w = p.z - floor(p.z);
        int i = floor(p.x);
        int j = floor(p.y);
        int k = floor(p.z);
        vec3 c[2][2][2];
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
        return perlin_interp(c, u, v, w);
    }
    float turb(const vec3& p, int depth = 7) const {
        float accum = 0;
        vec3 temp_p = p;
        float weight = 1.0;
        for (int i = 0; i < depth; i++) {
            accum += weight*noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }
        return fabs(accum);
    }
    static vec3 *ranvec;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;
};

static vec3* perlin_generate() {
    vec3 * p = new vec3[256];
    for (int i = 0; i < 256; ++i)
        p[i] = normalize(vec3(-1 + 2 * random::next(), -1 + 2 * random::next(), -1 + 2 * random::next()));
    return p;
}

static void permute(int *p, int n) {
    for (int i = n - 1; i > 0; i--) {
        int target = int(random::next()*(i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
    return;
}

static int* perlin_generate_perm() {
    int * p = new int[256];
    for (int i = 0; i < 256; i++)
        p[i] = i;
    permute(p, 256);
    return p;
}




#endif