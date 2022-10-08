#include <stdbool.h>

unsigned long gcd(unsigned long a, unsigned long b);
unsigned long eulers_totient(unsigned long p, unsigned long q);
unsigned int sieve_of_eratosthenes(unsigned int n, unsigned int** output);
bool isprime(unsigned long n);
bool isprime_eratos(unsigned long n, unsigned int* first_primes, int amount);
unsigned long power(unsigned long base, int exp);
unsigned long power2(int exp);
bool miller_rabin(unsigned long n, int k);
