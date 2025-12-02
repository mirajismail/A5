#ifndef PARTITION_H
#define PARTITION_H

#include <random>

// Function to randomly divide a number 'total' into a set of 'numdivision'
// numbers that add up to 'total'.
void rand_partition(std::mt19937& engine, int total, int nparts, int* nperpart);

#endif

