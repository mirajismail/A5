#include "output.h"
#include "linear.h"

void write_array(std::ofstream& f, int* a, int nrow, int ncol)
{
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++)
            f << a[linear(i,j,nrow,ncol)] << ' ';
        f << '\n';
    }
    f << '\n';
}

// count ants and determine min and max number on a square
void compute_stats(int* arr, int length, int& total, int& nmin, int& nmax)
{
    total = 0;
    nmin = 1e9;
    nmax = 0;

    for (int i = 0; i < length*length; i++) {
        int v = arr[i];
        total += v;
        if (v < nmin) nmin = v;
        if (v > nmax) nmax = v;
    }
}

