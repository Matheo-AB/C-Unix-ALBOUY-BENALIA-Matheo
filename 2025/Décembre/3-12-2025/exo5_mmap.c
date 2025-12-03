#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>



int main()
    {
        int status;

        int *compteur = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (compteur == MAP_FAILED)
            {
                perror("mmap");
                exit(EXIT_FAILURE);
            }
        *compteur = 0;

        if(fork == 0)
            {
                for(; *compteur < 10 ; *compteur++)
                    {
                        *compteur++;
                        printf("\n Le compteur Fils est : %d",*compteur);
                        sleep(1);
                    }
            }

        return 0;
    }