#include <rsa.h>
#include <generator.h>
#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int read_file(const char *path, char **contents);
int read_stdin(char **result);

struct arguments {
    // Mode of operation
    enum {GENERATE, ENCRYPT, DECRYPT, NONE} mode;
    // Keysize for generating
    int keysize;
    // Public or private keyfile to use
    char *identity;
    // File to encrypt or decrypt
    char *infile;
    // File to  save output to
    char *outfile;
};

const int GENERATE_KEY = 1000;
const int ENCRYPT_KEY = 1001;
const int DECRYPT_KEY = 1002;

static struct argp_option options[] = {
    {"generate", GENERATE_KEY, 0, 0, "Geneate a key"},
    {"encrypt", ENCRYPT_KEY, "FILE", OPTION_ARG_OPTIONAL, "Encrypt a file"},
    {"decrypt", DECRYPT_KEY, "FILE", OPTION_ARG_OPTIONAL, "Decrypt a file"},
    {"identity", 'i', "FILE", 0, "Keyfile to use"},
    {"output", 'o', "FILE", 0, "Output file"},
    {"keysize", 'k', "KEYSIZE", 0, "Keysize for generating"},
    {0}
};

error_t parse_opt (int key, char* arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case GENERATE_KEY:
            arguments->mode = GENERATE;
            break;
        case ENCRYPT_KEY:
            arguments->mode = ENCRYPT;
            arguments->infile = arg;
            break;
        case DECRYPT_KEY:
            arguments->mode = DECRYPT;
            arguments->infile = arg;
            break;
        case 'i':
            arguments->identity = arg;
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
        case ARGP_KEY_END:
            switch(arguments->mode) {
                case ENCRYPT:
                case DECRYPT:
                    if (arguments->identity == NULL) {
                        argp_failure(state, 1, 0, "Cannot do encryption/decryption without an identity");
                    }
                    break;
            }
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

struct argp argp = {options, parse_opt};

int main(int argc, char** argv) {

    struct PrivateKey key = generate_keypair(64);
    __int128_t c = encryptc(key.pub, 'A');
    char m = decryptc(key, c);
    printf("%c\n", m);

    return 0;
    
    struct arguments arguments;
    arguments.mode = NONE;
    arguments.keysize = 32;
    arguments.identity = NULL;
    arguments.infile = NULL;
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

int read_file(const char *path, char **contents) {
	FILE* file = fopen(path, "r");

	if (file == NULL) {
		perror("Failed to open file");
		return -1;
	}

	if (fseek(file, 0, SEEK_END) < 0) {
		perror("Failed to open file");
		return -1;
	}

	size_t file_size = ftell(file);
	rewind(file);

	// if (file_size == 0) {
	// 	fprintf(stderr, "Source file is empty\n");
	// 	return -1;
	// }

	char *buffer = malloc(file_size);
	size_t n_read = fread(buffer, 1, file_size, file);
	if (n_read < file_size) {
		perror("Failed to read file");
		return -1;
	}

	fclose(file);
	*contents = buffer;

	return (int) n_read;
}

int read_stdin(char **result) {
	int buffer_size = 1000;
	char *buffer = malloc(buffer_size);
	int length = 0;
	char c;
	while ((c=getchar()) != EOF) {
		if (length >= buffer_size) {
			buffer_size = buffer_size * 2;
			buffer = realloc(buffer, buffer_size);
		}
		buffer[length] = c;
		length++;
	}

	*result = buffer;
	return length;
}

