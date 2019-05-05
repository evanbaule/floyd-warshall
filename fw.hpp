#ifndef FW_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>

static float infinity = std::numeric_limits<float>::max();

void
generate(std::vector< std::vector <float> > &g, float w);

void
print_matrix(std::vector< std::vector <float> > g, int precision);



#endif // !FW_H


