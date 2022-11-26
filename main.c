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
};

error_t parse_opt (int key, char* arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case GENERATE_KEY:
            arguments->mode = GENERATE;
            break;
        case 'k':
            arguments->keysize = atoi(arg);
            break;
        case '0':
            arguments->outfile = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

}

struct argp argp = {options, parse_opt};

int main(int argc, char** argv) {

    struct arguments arguments;
    arguments.mode = NONE;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (arguments.mode == NONE) {
        printf("No mode\n");
        exit(1);
    }

    struct PrivateKey key = generate_keypair(32);

    long c = encryptc(key.pub, 'A');
    char m = decryptc(key, c);
    printf("%lu %c\n",c, m);

    long* cs = encrypt(key.pub, "pizza");
    char* ms = decrypt(key, cs);
    printf(ms);
}
