#include <primes.h>
#include <random.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long random_prime(int k) {
    // Use the upper half of total range
    unsigned long lower = power2((k-1)/2);
    unsigned long upper = power2(k/2)-1;
    
    unsigned long* first_primes;
    int amount = sieve_of_eratosthenes(163, &first_primes);
    
    unsigned long p = 0;
    while (!isprime_eratos(p, first_primes, amount)) {
        p = randlongrange(lower, upper); //* 2 - 1;
    }
    return p;
}

int main(int argc, char** argv) {
    //We want to generate 64 bit primes
    //So a keysize of 128 (k=128)
    int k = 32;

    srandom(time(NULL));
    unsigned long p = random_prime(k);
    unsigned long q = random_prime(k);
    unsigned long N = p * q;
    unsigned long phi = eulers_totient(p,q);


    unsigned long e;
    for (e=2;; e++) {
        if (gcd(e,phi) == 1) break;
    }

    printf("p: %lu q: %lu, N:%lu, phi: %lu, e:%lu\n", p,q,N,phi,e);

}
