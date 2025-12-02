#include "linear.h"

// Function to compute the linear index for a matrix embedded in a one-dimensional array
int linear(int row, int col, int nrow, int ncol) {
    return row * ncol + col;
}

