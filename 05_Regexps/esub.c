#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define BUFSIZE 1300
#define MAXGR 10

char* sed(char* substitution, char* pattern, regmatch_t* bags) {
    size_t len = 0;
    char* result = calloc(BUFSIZE, sizeof(*result));
    int begin, end;

    for (size_t i = 0; i < strlen(substitution); i++) {
        
        switch(substitution[i]) {
            case '\\':
                if (isdigit(substitution[i+1])) {
                    int br = substitution[i+1] - '0';
                    if (bags[br].rm_so >= 0) {
                        begin = bags[br].rm_so;
                        end = bags[br].rm_eo;
                        
                        char* tmp = calloc(strlen(result) + end - begin + 1, sizeof(*tmp));
                        snprintf(tmp, BUFSIZE, "%s%.*s", result, end - begin, pattern + begin);
                        free(result);
                        result = tmp;
                        
                        len = strlen(result);
                        i++;
                    } else {
                        printf("Invalid back reference %2s\n", substitution + i);
                        _exit(EXIT_FAILURE);
                    }
                    break;
                } 
            default:
                result[len++] = substitution[i];
                break;
        };
    }

    return result;
}

int main(int argc, char** argv) {
    char error_buf[BUFSIZE];
    int return_code, begin, end;

    regex_t regex;
    regmatch_t bags[MAXGR];
    

    if ((return_code = regcomp(&regex, argv[1], REG_EXTENDED))) {
        regerror(return_code, &regex, error_buf, BUFSIZE);
        printf("%s\n", error_buf);
        _exit(EXIT_FAILURE);
    }

    if ((return_code = regexec(&regex, argv[3], MAXGR, bags, 0))) {
        regerror(return_code, &regex, error_buf, BUFSIZE);
        printf("%s\n", error_buf);
        _exit(EXIT_FAILURE);
    }
    
    char* result = sed(argv[2], argv[3], bags);
    begin = bags[0].rm_so; end = bags[0].rm_eo;

    if (begin == end) {
        printf("%s\n", argv[3]);
    } else{
        char* fin = calloc(BUFSIZE, sizeof(*fin));

        argv[3][begin] = '\0';
        snprintf(fin, BUFSIZE, "%s%s", argv[3], result);    
        snprintf(result, BUFSIZE, "%s%s", fin, argv[3] + end);
        printf("%s\n", result);

        free(fin);
    }

    free(result);
    regfree(&regex);
    return 0;
}
