#include <stdlib.h>
#include <stdio.h>

long randlong() {
    FILE *fs;
    if (!(fs = fopen("/dev/random", "r")))
		return -1;
    long number;
    fread(&number, sizeof(long), 1, fs);
    fclose(fs);
    return number;
}

// randum number in [lower,upper]
long randlongrange(long lower, long upper) {
    return ( (unsigned long) randlong() % (upper - lower + 1)) + lower;
}
