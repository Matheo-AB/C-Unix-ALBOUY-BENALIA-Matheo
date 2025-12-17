#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int compteur_global = 0;
#define INCREMENT 11111111
#define THREAD_COUNT 99

void reset_compteur(void)
    {
        compteur_global = 0;
    }

int get_compteur(void)
    {
        return compteur_global;
    }

void* incrementeur_thread(void* arg)
    {
        for (int i = 0; i < INCREMENT; i++)
            {
                
                // TODO: Expliquer pourquoi, dans le détail, cette ligne qui pose problème
                compteur_global++;  // RACE CONDITION ICI !
                /*La race condition apparait sur un nombre important d'itérations.
                Lorsque que le compteur fait une itération, au bout de n itérations, il y a un risque de décalage.
                Le compteur affichera 11 alors qu'on sera à 12 par exemple care une incrémentation se fait en plusieurs phases.*/
            }
        return NULL;
    }

int executer_test(int nb_threads, int nb_increments)
    {
        reset_compteur();

        pthread_t* threads = malloc(nb_threads * sizeof(pthread_t));
            
        // Instancier un tableau de structure pour les arguments.
        int* args = malloc(nb_threads * sizeof(int));

        // Création des threads
        for (int i = 0; i < nb_threads; i++) 
            pthread_create(&threads[i], NULL, incrementeur_thread, NULL);

        for (int i = 0; i < nb_threads; i++)
            pthread_join(threads[i], NULL);

        int resultat = get_compteur();

        // Qu'est ce qui a été oublié ici ?
        // La libération de mémoire du malloc a été oubliée.
        free(threads);
        free(args);
        return resultat;

        return resultat;
    }

int main(void)
    {
        const int NB_TESTS = 50;
        const int NB_THREADS = 9;
        const int NB_INCREMENTS = 1111111;
        const int ATTENDU = NB_THREADS * NB_INCREMENTS;

        printf("=== Test Race Condition ===\n");
        printf("Configuration : %d threads × %d incréments\n", NB_THREADS, NB_INCREMENTS);
        printf("Valeur attendue : %d\n\n", ATTENDU);

        int nb_corrects = 0;
        int min = ATTENDU;
        int max = 0;

        for (int test = 0; test < NB_TESTS; test++)
            {
                int resultat = executer_test(NB_THREADS, NB_INCREMENTS);

                if (resultat == ATTENDU)
                    {
                        nb_corrects++;
                        printf("Test %2d : %d v \n", test + 1, resultat);
                    }
                else
                    {
                        printf("Test %2d : %d x (différence: %d)\n", test + 1, resultat, ATTENDU - resultat);
                    }
                if (resultat < min) min = resultat;
                if (resultat > max) max = resultat;
            }

        printf("\n=== Statistiques ===\n");
        printf("Tests corrects : %d/%d (%.1f%%)\n", nb_corrects, NB_TESTS, (100.0 * nb_corrects) / NB_TESTS);
        printf("Valeur min : %d (perte de %d)\n", min, ATTENDU - min);
        printf("Valeur max : %d\n", max);

        return 0;
    }
