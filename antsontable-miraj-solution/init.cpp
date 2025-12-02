#include "init.h"
#include "linear.h"


// initially place the ants evenly on the table
void initialize_ants(int* arr, int length, int total_ants)
{
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int n = linear(i, j, length, length);
            arr[n] = ((long long)(n+1) * total_ants) / (length*length)
                   - ((long long)(n)   * total_ants) / (length*length);
        }
    }
}

