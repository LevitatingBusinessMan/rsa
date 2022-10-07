#include <primes.h>
#include <random.h>
#include <time.h>

unsigned long random_prime(int k) {
    unsigned long lower = power(2,30);
    unsigned long upper = power(2,31);
    printf("%lu %lu\n", lower, upper);
    unsigned long p;
    while (!isprime(p)) {
        p = randint(lower, upper); //* 2 - 1;
    }
    return p;
}

int main(int argc, char** argv) {
    //We want to generate 64 bit primes
    //So a keysize of 128 (k=128)
    int k = 128;

    srand(time(NULL));
    printf("%lu\n", random_prime(k));
        
}
