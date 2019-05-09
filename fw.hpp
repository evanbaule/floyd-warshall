#ifndef FW_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>

typedef struct result
{
    int** dist;
    int** paths;
    bool neg_cycle;
} result;

static int INF = 99999;
constexpr bool dev_print = false;
constexpr int vexp = 2;
static unsigned long e_seed = 923901283 & std::chrono::system_clock::now().time_since_epoch().count();
static unsigned long w_seed = 212144421 ^ std::chrono::system_clock::now().time_since_epoch().count();

result*
floyd_warshall(int v, int edge_chance, unsigned long long seed, bool p);

inline bool
detect_neg_floyd_warshall(int v, int edge_chance, int i);

#endif // !FW_H


