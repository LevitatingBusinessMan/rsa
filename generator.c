// gcc -I./include primes.c random.c generator.c -lm -o primes -g -O3
#include <primes.h>
#include <random.h>
#include <stdio.h>
#include <rsa.h>

__uint32_t random_prime(int k) {
    // Use the upper half of total range
    __uint128_t lower = power2((k-1)/2);
    __uint128_t upper = power2(k/2) - 1; //power2(64) ends up as 1
    
    unsigned int* first_primes;
    int amount = sieve_of_eratosthenes(163, &first_primes);
    
    __uint128_t p = 0;
    while (!isprime_eratos(p, first_primes, amount)) {
        p = randlongrange(lower, upper);
    }
    return p;
}

struct PrivateKey generate_keypair(int k) {
    __uint128_t p = random_prime(k);
    __uint128_t q = random_prime(k);
    __uint128_t N = p * q;
    __uint128_t phi = eulers_totient(p,q);
    //__uint128_t lambda = carmicheals_totient(p,q);

    __uint128_t e;
    __uint128_t d;
    __int128_t y;
    for (e=3;; e++) {
        if (extended_gcd(e,phi,&d,&y) == 1) break;
    }

    if ((__int128_t) d < 1) {
        d += phi;
    }

    //This stopped working once I started using 128 bit ints
    //fprintf(stderr,"p: %lu, q: %lu, N:%lu, phi: %lu,  e:%lu, d:%lu\n", p,q,N,phi,e,d);

    struct PrivateKey key = {
        {e,N},
        p,
        q,
        d
    };

    return key;
}
