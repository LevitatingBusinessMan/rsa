#include <stdlib.h>
#include <stdio.h>

long randlong() {
    FILE *fs;
    char number[8];

    if (!(fs = fopen("/dev/urandom", "r")))
		return -1;
    for (int i=0; i<8; i++) {
        char c = fgetc(fs);
        number[i] = c;
    }
    fclose(fs);
    return (long) number;
}

// randum number in [lower,upper]
long randlongrange(long lower, long upper) {
    return ((long) randlong % (upper - lower + 1)) + lower;
}
