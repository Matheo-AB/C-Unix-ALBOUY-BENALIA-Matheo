#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

// Initialisation statique du mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static int compteur_global = 0;

void reset_compteur(void)
    {
        compteur_global = 0;
    }

int get_compteur(void)
    {
        int val;
        pthread_mutex_lock(&mutex);
        val = compteur_global;
        pthread_mutex_unlock(&mutex);
        return val;
    }

void* incrementeur_thread(void* arg)
    {
        int nb_increments = *(int*)arg;

        for (int i = 0; i < nb_increments; i++)
            {
                pthread_mutex_lock(&mutex);
                compteur_global++; 
                pthread_mutex_unlock(&mutex);
            }
        return NULL;
    }

int executer_test(int nb_threads, int nb_increments) 
    {
        reset_compteur();
        pthread_t* threads = malloc(nb_threads * sizeof(pthread_t));
        int* args = malloc(nb_threads * sizeof(int));

    for (int i = 0; i < nb_threads; i++)
        {
            args[i] = nb_increments;
            pthread_create(&threads[i], NULL, incrementeur_thread, &args[i]);
        }

    for (int i = 0; i < nb_threads; i++)
        {
            pthread_join(threads[i], NULL);
        }

        int resultat = get_compteur();

        free(threads);
        free(args);
        return resultat;
    }

int main(void)
    {
        const int NB_TESTS = 10;
        const int NB_THREADS = 50;
        const int NB_INCREMENTS = 10000000;
        const int ATTENDU = NB_THREADS * NB_INCREMENTS;

        printf("=== Test Compteur (Sécurisé) ===\n");
        printf("Attendu : %d\n\n", ATTENDU);

        for (int test = 0; test < NB_TESTS; test++)
            {
                int resultat = executer_test(NB_THREADS, NB_INCREMENTS);
                if (resultat == ATTENDU)
                    printf("Test %d : %d [OK]\n", test + 1, resultat);
                else
                    printf("Test %d : %d [ECHEC]\n", test + 1, resultat);
            }

        return 0;
    }