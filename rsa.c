#include <rsa.h>
#include <string.h>

long encryptc(struct PublicKey key, char m) {
    return modpower(m,key.e, key.N);
}

char decryptc(struct PrivateKey key, long c) {
    return modpower(c,key.d,key.pub.N);
}

long* encrypt(struct PublicKey key, char* m) {
    int length = strlen(m);
    long* c = malloc(length * sizeof(long) +1);
    for (int i=0; i < length; i++) c[i] = encryptc(key, m[i]);
    c[length] = 0;
    return c;
}

char* decrypt(struct PrivateKey key, long* c) {
    int length = 0;
    for (;c[length] != 0; length++);
    char *m = malloc(length);
    for (int i=0; i < length; i++) m[i] = decryptc(key, c[i]);
    m[length] = 0;
    return m;
}
