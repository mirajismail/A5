#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <random>

struct direction { int di; int dj; };

extern const int nmoves;
extern const direction moves[];

void do_timestep(
    std::mt19937& engine,
    int* ants,
    int* new_ants,
    int length,
    int* partition
);

#endif

