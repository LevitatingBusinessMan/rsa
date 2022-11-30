CC=gcc
CFLAGS=-I./include -lm -g -O3
rsa: primes.c random.c generator.c rsa.c main.c base64.c
	$(CC) $(CFLAGS) primes.c random.c generator.c rsa.c main.c base64.c -o rsa
