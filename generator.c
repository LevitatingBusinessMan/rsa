#include <primes.h>
#include <random.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct PublicKey {
    unsigned long e;
    unsigned long N;
};

struct PrivateKey {
    struct PublicKey pub;
    unsigned long p;
    unsigned long q;
    unsigned long d;
};

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

long encryptc(struct PublicKey key, char m) {
    return modpower(m,key.e, key.N);
}

char decryptc(struct PrivateKey key, long c) {
    return modpower(c,key.d,key.pub.N);
}

int main(int argc, char** argv) {
    int k = 32;

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

    struct PrivateKey key = {
        {e,N},
        p,
        q,
        d
    };

    long c = encryptc(key.pub, 'A');
    char m = decryptc(key, c);
    printf("%d %c",c, m);

}
