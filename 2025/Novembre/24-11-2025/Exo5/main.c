#include <stdio.h>

#define SQUARE(x) (x)*(x)
#define DOUBLE(x) 2*x

int main(int argc, char *argv[])
    {
        printf("%d\n" , SQUARE(3));
        printf("%d\n" , SQUARE(5));
        printf("%d\n" , SQUARE(3+2));
        return 0;
    }