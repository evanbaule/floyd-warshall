#ifndef FW_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <limits>


static int infinity = 999;
static unsigned long e_seed = 923901283 & std::chrono::system_clock::now().time_since_epoch().count();
static unsigned long w_seed = 212144421 ^ std::chrono::system_clock::now().time_since_epoch().count();
static int brk_len = 120;

void
brk(int len);

void
generate(std::vector< std::vector <int> > &g, int w);

void
print_matrix(std::vector< std::vector <int> > g);

#endif // !FW_H


