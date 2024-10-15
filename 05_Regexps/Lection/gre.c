#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>

#define MAXGR 10

int main(int argc, char** argv) {
    char* buf;
    size_t len = 0;
    int chars, begin, end;

    regex_t regex;
    regmatch_t bags[MAXGR];
    

    if (regcomp(&regex, argv[1], REG_EXTENDED)) {
    	_exit(1);
    }

    for (buf = NULL; (chars = getline(&buf, &len, stdin)) != -1; buf = NULL) {
        buf[chars-1] = 0;
        
        if (regexec(&regex, buf, MAXGR, bags, 0) == 0) {
        	for (int i = 0; i < MAXGR && bags[i].rm_so >= 0; i++ ) {
        		begin = bags[i].rm_so;
        		end = bags[i].rm_eo;
        		printf("%d: %.*s\n", i, end - begin, buf + begin);
        	}
        }
        
        free(buf);
    }
    regfree(&regex);
    return 0;
}