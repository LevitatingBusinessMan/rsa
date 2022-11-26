CC=gcc
CFLAGS=-I./include -lm -g -O3
rsa: primes.c random.c generator.c rsa.c main.c
	$(CC) $(CFLAGS) primes.c random.c generator.c rsa.c main.c -o rsa
