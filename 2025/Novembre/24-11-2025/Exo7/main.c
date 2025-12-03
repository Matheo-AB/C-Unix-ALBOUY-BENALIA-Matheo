#include <stdio.h>

#define DEBUG

int main(int argc, char *argv[])
    {
        #ifdef DEBUG
        printf("Le programme utilise DEBUG! \n");
        #elif 
        printf("Le programme n'utilise pas DEBUG! \n");
        #endif
        return 0;
    }