#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <chrono>

#include "mtree.h"


std::vector<struct point*> generate_points(double n){

    std::vector<Point*> ret(n);

    std::srand((unsigned) std::time(NULL));

    for(int i = 0; i < n; i++){

        ret[i] = newPoint((double) rand() / RAND_MAX, (double) rand() / RAND_MAX);

    }

    return ret;

}
