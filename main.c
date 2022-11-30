#include <rsa.h>
#include <generator.h>
#include <stdio.h>
#include <argp.h>

struct arguments {
    enum {GENERATE, ENCRYPT, DECRYPT, NONE} mode;
    int keysize;
    char *outfile;
};

const int GENERATE_KEY = 1000;

static struct argp_option options[] = {
    {"generate", GENERATE_KEY, 0, 0, "Geneate a key"},
    {"output", 'o', "FILE", 0, "Output file"},
    {"keysize", 'k', "KEYSIZE", 0, "Keysize"},
    {0}
};

error_t parse_opt (int key, char* arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case GENERATE_KEY:
            arguments->mode = GENERATE;
            break;
        case 'k':
            arguments->keysize = atoi(arg);
            if (arguments->keysize == 0) {
                argp_failure(state, 1, 0, "Invalid keysize value");
                exit(1);
            }
            break;
        case '0':
            arguments->outfile = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct argp argp = {options, parse_opt};

int main(int argc, char** argv) {

    struct arguments arguments;
    arguments.mode = NONE;
    arguments.keysize = 32;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // TODO move this to parse_opt
    if (arguments.mode == NONE) {
        printf("No mode\n");
        exit(1);
    }

    struct PrivateKey key = generate_keypair(arguments.keysize);

    printf(privkey_to_ascii(key));
    printf(pubkey_to_ascii(key.pub));

    long c = encryptc(key.pub, 'A');
    char m = decryptc(key, c);
    printf("%lu %c\n",c, m);

    long* cs = encrypt(key.pub, "pizza");
    char* ms = decrypt(key, cs);
    printf(ms);
}
