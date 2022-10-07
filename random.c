#include <stdlib.h>

// randum number in [lower,upper]
int randint(long lower, long upper) {
    //return lower + (upper-lower) * ((double) rand() / (double) RAND_MAX + 0.5);
    return (rand() % (upper - lower + 1)) + lower;
}
