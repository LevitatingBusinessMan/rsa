struct PublicKey {
    __uint128_t e;
    __uint128_t N;
};

struct PrivateKey {
    struct PublicKey pub;
    __uint128_t p;
    __uint128_t q;
    __uint128_t d;
};

__int128_t encryptc(struct PublicKey key, char m);
char decryptc(struct PrivateKey key, __int128_t c);
__int128_t* encrypt(struct PublicKey key, char* m);
char* decrypt(struct PrivateKey key, __int128_t* c);
char* pubkey_to_ascii(struct PublicKey key);
char* privkey_to_ascii(struct PrivateKey key);
