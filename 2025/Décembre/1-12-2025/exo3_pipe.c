#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
    {
        int fd[2];
        pid_t pid;
        char buffer[1024];
        ssize_t nbytes;
        if (pipe(fd) == -1)
            {
                perror("Erreur lors de la création du pipe");
                exit(EXIT_FAILURE);
            }

        pid = fork();

        if (pid == -1)
            {
                perror("Erreur fork");
                exit(EXIT_FAILURE);
            }

        if (pid == 0)
            {
                close(fd[1]);
                printf("Fils : Lecture.\n");
                while ((nbytes = read(fd[0], buffer, sizeof(buffer))) > 0)
                    {
                        write(STDOUT_FILENO, buffer, nbytes);
                    }
                printf("\nFils : Fin de lecture (EOF détecté).\n");
                close(fd[0]);
                exit(0);
            }
        else
            {
                close(fd[0]);
                const char *message = "Bonjour depuis le père.\nCeci est une deuxième ligne.\n";
                write(fd[1], message, strlen(message));
                sleep(1);
                close(fd[1]);
                wait(NULL);
                printf("Père : Le fils a terminé.\n");
            }
        return 0;
    }
//Si l'extrémité n'est pas fermée, l'hors de l'éxécution du programme, le fils attendra toujours une réponse du père. Il attendra que le père est terminé son action d'écriture.
//Si le père ne ferme pas le fd[1], l'hors de la lecture, l'action du fils va être bloqué en attente de fermeture pour le réouvrir. Il ne peut pas ouvrir un signal qui est déjà ouvert.