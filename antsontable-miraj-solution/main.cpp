#include <iostream>
#include <fstream>
#include <random>

#include "init.h"
#include "timestep.h"
#include "output.h"

int main() {
    int length = 70;
    int ntimesteps = 10000;
    int total_ants = 40000;
    size_t seed = 120;

    // dynamically allocated arrays
    int* ants = new int[length * length];
    int* new_ants = new int[length * length];
    int* partition = new int[nmoves];

    std::mt19937 engine(seed);
    std::ofstream out("ants.txt");

    // initialize
    initialize_ants(ants, length, total_ants);

    int nmin, nmax;
    compute_stats(ants, length, total_ants, nmin, nmax);
    std::cout << 0 << " " << total_ants << " " << nmin << " " << nmax << "\n";
    write_array(out, ants, length, length);

    // simulate
    for (int t = 1; t <= ntimesteps; t++) {
        do_timestep(engine, ants, new_ants, length, partition);
        compute_stats(ants, length, total_ants, nmin, nmax);
        std::cout << t << " " << total_ants << " " << nmin << " " << nmax << "\n";
        write_array(out, ants, length, length);
    }

    delete[] ants;
    delete[] new_ants;
    delete[] partition;
    return 0;
}

