#include <stdbool.h>

__uint128_t gcd(__uint128_t a, __uint128_t b);
__uint128_t eulers_totient(__uint128_t p, __uint128_t q);
unsigned int sieve_of_eratosthenes(unsigned int n, unsigned int** output);
bool isprime(__uint128_t n);
bool isprime_eratos(__uint128_t n, unsigned int* first_primes, int amount);
__uint128_t power(__uint128_t base, __uint128_t exp);
__uint128_t power2(__uint128_t exp);
bool miller_rabin(__uint128_t n, int k);
__uint128_t carmicheals_totient(__uint128_t p, __uint128_t q);
__uint128_t lcm(__uint128_t a, __uint128_t b);
__int128_t extended_gcd(__int128_t a, __int128_t b, __int128_t* x, __int128_t* y);
__uint128_t modpower2(__uint128_t exp, __uint128_t mod);
__uint128_t modpower(__uint128_t base, __uint128_t exp, __uint128_t mod);
