#include "partition.h"
#include <algorithm>

void rand_partition(std::mt19937& engine, int total, int nparts, int* nperpart)
{
    std::uniform_int_distribution<int> dist(0, total);

    nperpart[0] = 0;
    for (int k = 1; k < nparts; k++)
        nperpart[k] = dist(engine);

    std::sort(nperpart, nperpart + nparts);

    for (int k = 0; k < nparts - 1; k++)
        nperpart[k] = nperpart[k+1] - nperpart[k];

    nperpart[nparts - 1] = total - nperpart[nparts - 1];
}

