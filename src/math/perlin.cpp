#include "perlin.h"
//vec3* perlin::ranvec = perlin::generate();
//int* perlin::permX= perlin::generatePerm();
//int* perlin::permY= perlin::generatePerm();
//int* perlin::permZ= perlin::generatePerm();
vec3 *perlin::ranvec = perlin_generate();
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();