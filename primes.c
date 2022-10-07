#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

unsigned int sieve_of_eratosthenes(unsigned int n, unsigned int** output) {
    bool* primes = malloc(sizeof(bool) * (n+1));
    //bool primes[n+1];
    memset(primes, true, sizeof(bool) * (n+1));
    
    // 0 and 1 are not primes
    primes[0] = primes[1] = false;
    unsigned int primes_count = n-1;

    unsigned int square_root_n = sqrt(n);

    for (size_t i = 2; i <= square_root_n; i++) {
        if (primes[i]) {
            for (size_t j = i*i; j < n; j += i) {
                primes[j] = false;
            }
        }
    }

    primes_count = 0;
    for (size_t i = 2; i <= n+1; i++) {
        if (primes[i]) primes_count++;
    }

    unsigned int* real_primes;
    real_primes = (unsigned int*) malloc(primes_count * sizeof(int));
    size_t cursor = 0;

    for (size_t i = 0; i <= n; i++) {
        if (primes[i]) {
            real_primes[cursor] = i;
            cursor++;
        }
    }

    *output = real_primes;

    return primes_count;

}
