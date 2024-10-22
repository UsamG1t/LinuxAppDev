#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        int i;
        char *s;

        s = strdup(argv[argc-1]);
        for(i=0; i<4; i++)
                printf("%s: %d, %d\n", s, rand(), i*2+1);

        return 0;
}
