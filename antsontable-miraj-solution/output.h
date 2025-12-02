#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>

void write_array(std::ofstream& out, int* arr, int nrow, int ncol);
void compute_stats(int* arr, int length, int& total, int& nmin, int& nmax);

#endif

