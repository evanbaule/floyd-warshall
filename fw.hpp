#ifndef FW_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>

static float infinity = std::numeric_limits<float>::max();
static unsigned long e_seed = 923901283 & std::chrono::system_clock::now().time_since_epoch().count();
static unsigned long w_seed = 212144421 ^ std::chrono::system_clock::now().time_since_epoch().count();

void
generate(std::vector< std::vector <float> > &g, float w);

void
print_matrix(std::vector< std::vector <float> > g, int precision);



#endif // !FW_H


