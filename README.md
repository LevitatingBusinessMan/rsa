# RSA
This is my own implementation of the [RSA cryptosystem](https://en.wikipedia.org/wiki/RSA_(cryptosystem)). It's written in plain C (no bignum libraries) and supporst keysizes up to 32 bits.

References:  
https://security.stackexchange.com/questions/176394/how-does-openssl-generate-a-big-prime-number-so-fast  
https://stackoverflow.com/questions/13665443/generate-random-prime-number-in-c-c-between-2-limits  
https://en.wikipedia.org/wiki/Primality_test  
https://crypto.stackexchange.com/questions/76253/requirements-for-rsa-key-parameters  
https://github.com/openssl/openssl/blob/master/crypto/bn/bn_prime.c  
https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes  
https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test  
https://man.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man3/arc4random.3?query=arc4random&sec=3 (-lbsd)  
https://man7.org/linux/man-pages/man2/getrandom.2.html  
https://gmplib.org/  
https://home.cs.colorado.edu/~srirams/courses/csci2824-spr14/gmpTutorial.html  
https://math.stackexchange.com/questions/1226742/rsa-and-extended-euclidian-algorithm  
