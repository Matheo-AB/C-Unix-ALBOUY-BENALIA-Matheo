#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main()
    {
        int status;
        pid_t pid;

        int *compteur = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (compteur == MAP_FAILED)
            {
                perror("mmap");
                exit(EXIT_FAILURE);
            }
        *compteur = 0;

    /**    int *compteur2 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        if (compteur2 == MAP_FAILED)
            {
                perror("mmap");
                exit(EXIT_FAILURE);
            }
        *compteur2 = 0;*/

        if(pid == 0)
            {
                for(int i=0; i < 10 ; i++)
                    {
                        (*compteur)++;
                        printf("\n Le compteur Fils est : %d",*compteur);
                        fflush(stdout); //Forcer l'affichage
                        sleep(1);
                    }
                exit(0);
                printf("La valeur finale du compteur père est : %d\n",*compteur);
            }
        while(fork == 0)
            {
                printf("\n Le compteur Père est : %d",*compteur);
                wait(NULL);
            }
        printf("La valeur finale du compteur père est : %d\n",*compteur);
        return 0;
        munmap(compteur, sizeof(int));
    }
