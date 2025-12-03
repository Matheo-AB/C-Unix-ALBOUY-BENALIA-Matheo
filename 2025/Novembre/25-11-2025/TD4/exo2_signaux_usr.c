#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
    {
        pid_t pid;
        int status;
        pid = fork();

        if (pid == 0)
            {
                printf("Je suis l'enfant et mon PID est : %d\n", getpid());
                sleep(2);
                //printf("Le PID du processus : %s", pid);
                exit(42);
            }

        else if (pid > 0)
            {
                printf("Je suis le parent avec PID %d, de l'enfant %d\n", getpid(), pid);
                pid = wait(&status);
                if(WIFEXITED(status))
                    {
                        printf("\nEnfant crée avec le statut %d\n", status);                        
                        exit(10);
                    }
            
            } 
        else
            {
                perror("fork");
                exit(-1);
            }
    }