#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
    {
        int p[2];
        int status1, status2;

        if (pipe(p) == -1)
            {
                perror("pipe");
                exit(1);
            }

        if (fork() == 0)
            {
                dup2(p[1], STDOUT_FILENO);

                close(p[0]);
                close(p[1]);

                for (int i = 0; i < 10; i++)
                    {
                        printf("%d\n", i);
                    }
                exit(0);
            }
        if (fork() == 0)
            {
                dup2(p[0], STDIN_FILENO);
                close(p[0]);
                close(p[1]);
                int val;
                while (scanf("%d", &val) != EOF)
                    {
                        if (val % 2 == 0)
                            {
                                printf("Filtre (Pair) : %d\n", val);
                            }
                    }
                exit(0);
            }   
        close(p[0]);
        close(p[1]);
        wait(&status1);
        wait(&status2);
        printf("Père : Tous les traitements sont finis.\n %d", status1, status2);
        return 0;
    }
//La différence entre ces deux types de pipe est : qu'un pipe brut ne permet pas d'enregister le résultat dans une variable alors que la redirection vers stdin/stdout permet d'enregistrer ou d'afficher la variable.
//L'effet que possède dup2 dans cet exercice est le suivant : permet de rediger la sortie d'un pipe vers stdin ou stdout.