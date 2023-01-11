//This file contains most algorithms

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <random.h>
#include <primes.h>

__uint128_t eulers_totient(__uint128_t p, __uint128_t q) {
    return (p-1) * (q-1);
}

__uint128_t carmicheals_totient(__uint128_t p, __uint128_t q) {
    return lcm(p-1, q-1);
}
__uint128_t gcd(__uint128_t a, __uint128_t b) {
    if (a && b) for(;(a %= b) && (b %= a););
    return a | b;
}

__uint128_t lcm(__uint128_t a, __uint128_t b) {
    __int128_t lcm;
    __int128_t step;
    __int128_t max = step =  a > b ? a : b;
    for(;;) {
        if (max % a == 0 && max % b == 0) {
            lcm = max;
            break;
        }
        max += step;
    }
    return lcm;
}

// This sometimes returns a different answer than the gcd function
// which is a bug
__int128_t extended_gcd(__int128_t a, __int128_t b, __int128_t* x, __int128_t* y) {
    __int128_t old_r = a;
    __int128_t r = b;
    __int128_t old_s = 1;
    __int128_t s = 0;
    __int128_t old_t = 0;
    __int128_t t = 1;

    while (r != 0) {
        __int128_t quotient = old_r / r;
        
        __int128_t prov = r;
        r = old_r - quotient * prov;
        old_r = prov;
        
        prov = s;
        s = old_s - quotient * prov;
        old_s = prov;
        
        prov = t;
        t = old_t - quotient * prov;
        old_t = prov;
    }

    // printf("Bezout coefficients: %li %li\n", old_s, old_t);
    // printf("Greates common divisor: %li\n", old_r);
    // printf("Real gcd: %li\n", gcd(a,b));
    // printf("Quotients: %li %lu\n", t, s);

    *x = old_s;
    *y = old_t;
    
    return old_r;
}

//fails on 151
unsigned int sieve_of_eratosthenes(unsigned int n, unsigned int** output) {
    bool* primes = malloc(sizeof(bool) * (n+1));
    //bool primes[n+1];
    memset(primes, true, sizeof(bool) * (n+1));
    
    // 0 and 1 are not primes
    primes[0] = primes[1] = false;
    
    unsigned int square_root_n = sqrt(n);

    for (size_t i = 2; i <= square_root_n; i++) {
        if (primes[i]) {
            for (size_t j = i*i; j < n; j += i) {
                primes[j] = false;
            }
        }
    }

    unsigned int primes_count = 0;
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

__uint128_t power2(__uint128_t exp) {
    return (__uint128_t) 1 << exp;
}

__uint128_t power(__uint128_t base, __uint128_t exp) {
    if (base == 2) return power2(exp);
    int i;
    __uint128_t result = 1;
    for (i = 0; i < exp; i++) result *= base;
    return result;
}

__uint128_t modpower2(__uint128_t exp, __uint128_t mod) {
    __uint128_t res = 1;
    for (;exp >= 1; exp--) {
        res = (res << 1) % mod;
    }
    return res;
}

// Memory efficient modular exponentation with exponentation by squaring
__uint128_t modpower(__uint128_t base, __uint128_t exp, __uint128_t mod) {
    if (base == 2) return modpower2(exp,mod);
    int i;
    __uint128_t result = 1;
    while (exp > 0) {
        // Odd exponent
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = base * base % mod;
    }
    return result;
}

//fails on 679
//infinite loop 18446744072410345099
bool isprime(__uint128_t n) {
    if (!(n&1) || !(n%3) || n <= 1) return false;

    if (n == 2 || n == 3) return true;

    //if (!miller_rabin(n,1)) return false;

    unsigned int square_root_n = sqrt(n);
    for (int i=5; i<= square_root_n; i += 6) {
        if (n % i == 0 || n % (1+2) == 0) return false;
    }

    return true;
}

bool isprime_eratos(__uint128_t n, unsigned int* first_primes, int amount) {
    for (int i=0; i<amount; i++) {
        if (n % first_primes[i] == 0) return false;
    }

    return isprime(n);
}

// This function is quite useless as it won't work for primes which create a large d
// as this will cause an integer overflow if used as an exponent of a large base.
bool miller_rabin(__uint128_t n, int k) {    
    //write n as 2^s*d+1 where d is odd
    __uint128_t a;
    __uint128_t s = 0;
    __uint128_t d = n-1;

    if (!(n&1) || !(n%3) || n <= 1) return false;

    if (n == 2 || n == 3) return true;

    //Divide d by two until it's odd
    //incrementing s each time
    while (!(d&1)) {
        d >>=1;
        s++;
    }

    for (int i=0; i<k; i++) {
        a = randlongrange(2,n-2); // testing 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37 should suffice for n < 2**64
        __uint128_t x = modpower(a, d, n);
        if (x == 1 || x == n -1 ) continue;
        for (int j=0; j < s-1; j++) {
            x = x*x % n;
            if (x == n - 1) break;
        }
        return (x == n - 1);
    }
    return true;
}
