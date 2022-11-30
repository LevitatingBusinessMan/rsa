#include <rsa.h>
#include <generator.h>
#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

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
        case 'o':
            arguments->outfile = arg;
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
    arguments.outfile = NULL;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    switch (arguments.mode) {
        // I could move this case to the argp parser
        case NONE:
            printf("No mode\n");
            exit(1);
        case GENERATE:
            struct PrivateKey key = generate_keypair(arguments.keysize);

            if (arguments.outfile == NULL) {
                printf(privkey_to_ascii(key));
                printf("\n");
                printf(pubkey_to_ascii(key.pub));
            } else {
                FILE* fpriv = fopen(arguments.outfile, "w");
                if (fpriv == NULL) {
                    perror("Error opening file");
                    exit(errno);
                }
                
                char* pubkeyfilepath = malloc(strlen(arguments.outfile) + 4);
                sprintf(pubkeyfilepath, "%s.pub", arguments.outfile);
                FILE* fpub = fopen(pubkeyfilepath, "w");
                if (fpub == NULL) {
                    perror("Error opening file");
                    exit(errno);
                }

                char* privkey = privkey_to_ascii(key);
                fwrite(privkey, strlen(privkey), 1, fpriv);
                fclose(fpriv);
                if (chmod(arguments.outfile, strtol("600",0,8)) < 0) {
                    perror("Error changing permissions");
                    exit(errno);
                }
                printf("Keyfile %s created\n", arguments.outfile);

                char* pubkey = pubkey_to_ascii(key.pub); 
                fwrite(pubkey, strlen(pubkey), 1, fpub);
                fclose(fpub);
                if (chmod(pubkeyfilepath, strtol("644",0,8)) < 0) {
                    perror("Error changing permissions");
                    exit(errno);
                }
                printf("Keyfile %s created\n", pubkeyfilepath);               
            } 

            break;
    }
}
