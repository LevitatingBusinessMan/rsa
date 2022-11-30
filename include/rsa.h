struct PublicKey {
    unsigned long e;
    unsigned long N;
};

struct PrivateKey {
    struct PublicKey pub;
    unsigned long p;
    unsigned long q;
    unsigned long d;
};

long encryptc(struct PublicKey key, char m);
char decryptc(struct PrivateKey key, long c);
long* encrypt(struct PublicKey key, char* m);
char* decrypt(struct PrivateKey key, long* c);
char* pubkey_to_ascii(struct PublicKey key);
char* privkey_to_ascii(struct PrivateKey key);
