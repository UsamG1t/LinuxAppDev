#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "rhash.h" /* LibRHash interface */
#include "config.h"

#ifdef NO_READLINE
#define NO_READLINE 1
#else
#define NO_READLINE 0
#endif

enum
{
    HASH_SIZE = 5,
    SRC_SIZE = 100,
    DIGEST_SIZE = 64,
    DST_SIZE = 130
};

int my_read(char** buf, size_t* len) {
    if (HAVE_LIBREADLINE && !NO_READLINE) {
        *buf = readline("> ");
        if (*buf && **buf && **buf != '\n') {
            *len = strlen(*buf);
            add_history(*buf);
        }

        return *len ? *len : -1;
    }

    return getline(buf, len, stdin);
}

int main(int argc, char** argv) {
char hash_type[HASH_SIZE] = {};
char src[SRC_SIZE] = {};

unsigned char digest[DIGEST_SIZE];
char dst[DST_SIZE];

int hash_flag = 0;
int dst_flags = 0;

rhash_library_init(); /* initialize static data */
// initialize_readline();

char* buf = NULL;
size_t len = 0;

if (HAVE_LIBREADLINE && !NO_READLINE) {
    // printf("<>\n");
    rl_bind_key('\t', rl_insert);
}

// while (getline(&buf, &len, stdin) != -1) {
while (my_read(&buf, &len) != -1) {
    if (sscanf(buf, "%s %s", hash_type, src) != 2) {
        fprintf(stderr, "Incorrect request\n");
        if (buf) {
            free(buf);
        }
        len = 0;
        continue;
    }

    dst_flags = (hash_type[0] >= 'A' && hash_type[0] <= 'Z') \
            ? RHPR_BASE64 : RHPR_HEX;
    
    if (!strncmp(hash_type, "MD5", 3) ||
        !strncmp(hash_type, "md5", 3)) {
        hash_flag = RHASH_MD5;
    } else if (!strncmp(hash_type, "SHA1", 4) ||
               !strncmp(hash_type, "sha1", 4)) {
        hash_flag = RHASH_SHA1;
    } else if (!strncmp(hash_type, "TTH", 3) ||
               !strncmp(hash_type, "tth", 3)) {
        hash_flag = RHASH_TTH;
    } else {
        fprintf(stderr, "Incorrect hash\n");
        if (buf) {
            free(buf);
        }
        len = 0;
        continue;
    }

    if (src[0] == '\"') {
        // str
        if (rhash_msg(hash_flag, src+1, strlen(src+1), digest) < 0) {
            fprintf(stderr, "Src digest calculation error\n");
            if (buf) {
                free(buf);
            }
            len = 0;
            continue;
        }
    } else {
        // file
        if (rhash_file(hash_flag, src, digest) < 0) {
            fprintf(stderr, "LibRHash error: %s: %s\n", src, strerror(errno));
            if (buf) {
                free(buf);
            }
            len = 0;
            continue;
        }
    }

    rhash_print_bytes(dst, digest, rhash_get_digest_size(hash_flag), dst_flags);

    printf("%s\n", dst);
}

return 0;
}