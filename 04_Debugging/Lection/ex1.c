#include <stdio.h>
int N = 42;


int fun2(int n) {
        return n*2+1;
}

int fun1(int c) {
        c += 1;
        return fun2(c) + fun2(c*2);
}

int main(int argc, char *argv[]) {
        int i;

        for(i=0; i <10; i++)
                printf("%d\n", fun1(N+i));
        return 0;
}