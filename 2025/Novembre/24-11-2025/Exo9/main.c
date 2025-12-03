#include <stdio.h>

#define LOG(msg)
#define DEBUG

int main(int argc, char *argv[])
    {   
        #ifdef DEBUG
        LOG(Le programme utilise le DEBUG)
        LOG(Le programme est terminé)

        return 0;
    }