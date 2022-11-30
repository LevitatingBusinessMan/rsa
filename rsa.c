#include <rsa.h>
#include <string.h>
#include <stdlib.h>
#include <primes.h>
#include <base64.h>
#include <string.h>
#include <stdio.h>

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


char* pubkey_to_ascii(struct PublicKey key) {
    int base64len = Base64encode_len(sizeof(key));
    char* base64buf = malloc(base64len);
    Base64encode(base64buf, (char*) &key, sizeof(key));

    char* buffer = malloc(66 + base64len + 1);
    sprintf(
        buffer,
        "-----BEGIN REIN RSA PUBLIC KEY\n"
        "%s\n"
        "-----END REIN RSA PUBLIC KEY\n",
        base64buf
    );

    return buffer;
}

char* privkey_to_ascii(struct PrivateKey key) {
    int base64len = Base64encode_len(sizeof(key));
    char* base64buf = malloc(base64len);
    Base64encode(base64buf, (char*) &key, sizeof(key));

    char* buffer = malloc(66 + base64len + 1);
    sprintf(
        buffer,
        "-----BEGIN REIN RSA PRIVATE KEY\n"
        "%s\n"
        "-----END REIN RSA PRIVATE KEY\n",
        base64buf
    );

    return buffer;
}
