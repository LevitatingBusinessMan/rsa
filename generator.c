#include <primes.h>
#include <random.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long random_prime(int k) {
    // Use the upper half of total range
    unsigned long lower = power2((k-1)/2);
    unsigned long upper = power2(k/2) - (k == 128 ? 2 : 1); //power2(64) ends up as 1
    
    unsigned int* first_primes;
    int amount = sieve_of_eratosthenes(163, &first_primes);
    
    unsigned long p = 0;
    while (!isprime_eratos(p, first_primes, amount)) {
        p = randlongrange(lower, upper);
    }
    return p;
}

int main(int argc, char** argv) {
    //We want to generate 64 bit primes
    //So a keysize of 128 (k=128)
    int k = 64;

    srandom(time(NULL));
    unsigned long p = random_prime(k);
    unsigned long q = random_prime(k);
    unsigned long N = p * q;
    unsigned long phi = eulers_totient(p,q);
    //unsigned long lambda = carmicheals_totient(p,q);



    unsigned long e;
    unsigned long d;
    long y;
    for (e=3;; e++) {
        if (extended_gcd(e,phi,&d,&y) == 1) break;
    }

    if ((long) d < 1) {
        d += phi;
    }

    printf("p: %lu, q: %lu, N:%lu, phi: %lu,  e:%lu, d:%lu\n", p,q,N,phi,e,d);

}
