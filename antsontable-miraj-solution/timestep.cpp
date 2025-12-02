#include "timestep.h"
#include "partition.h"
#include "linear.h"

const int nmoves = 9;
const direction moves[nmoves] = {
    {-1,-1},{-1,0},{-1,1},
    { 0,-1},{ 0,0},{ 0,1},
    { 1,-1},{ 1,0},{ 1,1}
};

void do_timestep(
    std::mt19937& engine,
    int* ants,
    int* new_ants,
    int length,
    int* partition
) {
    int ncell = length * length;

    // zero out new_ants
    for (int k = 0; k < ncell; k++)
        new_ants[k] = 0;

    // move ants
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int idx = linear(i,j,length,length);
            int count = ants[idx];

            if (count <= 0) continue;
            // pick number of ants that take part in each move
            rand_partition(engine, count, nmoves, partition);
            // push ants in their respective directions
            for (int m = 0; m < nmoves; m++) {
                int i2 = i + moves[m].di;
                int j2 = j + moves[m].dj;
                // out in new_ants if not falling off the table
                if (i2 >= 0 && i2 < length && j2 >= 0 && j2 < length) {
                    int idx2 = linear(i2, j2, length, length);
                    new_ants[idx2] += partition[m];
                }
            }
        }
    }

    // copy back
    for (int k = 0; k < ncell; k++)
        ants[k] = new_ants[k];
}

