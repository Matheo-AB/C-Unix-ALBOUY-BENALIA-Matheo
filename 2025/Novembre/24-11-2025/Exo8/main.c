#include <stdio.h>

int main(int argc, char *argv[])
    {
        int notes[5] = {12, 14, 9, 15, 10};

        for (int i = 0 ; i<5 ; i++)
            {
                printf(" Note : %d \n" , notes[i]);
            }
        return 0;
    }