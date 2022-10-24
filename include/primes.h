#include <stdbool.h>

unsigned long gcd(unsigned long a, unsigned long b);
unsigned long eulers_totient(unsigned long p, unsigned long q);
unsigned int sieve_of_eratosthenes(unsigned int n, unsigned int** output);
bool isprime(unsigned long n);
bool isprime_eratos(unsigned long n, unsigned int* first_primes, int amount);
unsigned long power(unsigned long base, unsigned long exp);
unsigned long power2(unsigned long exp);
bool miller_rabin(unsigned long n, int k);
unsigned long carmicheals_totient(unsigned long p, unsigned long q);
unsigned long lcm(unsigned long a, unsigned long b);
long extended_gcd(long a, long b, long* x, long* y);
unsigned long modpower2(unsigned long exp, unsigned long mod);
unsigned long modpower(unsigned long base, unsigned long exp, unsigned long mod);
