#include <stdlib.h>
#include <stdio.h>

//This used to generate longs but generates 128 bit ints now
__int128_t randlong() {
    FILE *fs;
    if (!(fs = fopen("/dev/urandom", "r")))
		return -1;
    __int128_t number;
    fread(&number, sizeof(__int128_t), 1, fs);
    fclose(fs);
    return number;
}

// Generates a randum number in [lower,upper]
//This used to generate longs but generates 128 bit ints now
__int128_t randlongrange(__int128_t lower, __int128_t upper) {
    return ( (__int128_t) randlong() % (upper - lower + 1)) + lower;
}
