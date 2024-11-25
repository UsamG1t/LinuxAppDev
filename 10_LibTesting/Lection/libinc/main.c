#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main(int argc, char *argv[]) {
        int n;

        if(argc < 2) {
          fprintf(stderr, "Usage: %s NUMBER\n", argv[0]);
          return 1;
        }
        
        n = atoi(argv[1]);
        printf("%d\n", inc(n));

 return 0;
}
