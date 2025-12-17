#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>

#define TAILLE_DONNEES 10
#define MULTIPLICATEUR 1000

static const int DONNEES[TAILLE_DONNEES] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct
    {
        int valeur;
        int multiplicateur;
        int index;
    } args_t;

void* calcul_thread(void* arg)
    {
        // cette fonction est appelé via pthread_create
        // vous savez ce que représente @arg
        // vous notifié au compilateur "cette" address dois être considéré comme args_t
        args_t* args = (args_t*)arg;
        // vous pouvez accéder (read/write) a toutes les variables via `args->`
        return NULL;
    }

int main(void)
    {
        printf("=== Calcul Parallèle ===\n");

        struct timespec debut, fin;
        clock_gettime(CLOCK_MONOTONIC, &debut);
        // TODO: Créer un tableau de pthread_t
        args_t thread_args[10];

        // TODO: Créer un tableau de structures d'arguments
        for (int i = 0; i < 10; i++)
            {
                thread_args[i].index = i;
                thread_args[i].valeur = i + 1;
            }
                // TODO: Créer et démarrer tous les threads

        // TODO : Créer tous les threads
        for (int i = 0; i < 10; i++)
            {
                    // 1. On prépare les données pour le thread i
                thread_args[i].index = i;
                thread_args[i].valeur = i + 1; // Exemple de donnée à traiter

                pthread_create(&thread_args[i], NULL, calcul_thread, (void*)&thread_args[i]);
            }
        // TODO: Attendre tous les threads
        for (int i = 0; i < 10; i++)
            {
                pthread_join(thread_args[i], NULL); 
            }
        // TODO: Agréger les résultats

        int somme_total = 0;
        for (int i = 0; i < 10; i++)
            {
                somme_total += thread_args[i].resultat;
            }
    
    
        clock_gettime(CLOCK_MONOTONIC, &fin);
        long duree = (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_nsec - debut.tv_nsec) / 1000000;

        printf("Résultat total : %ld\n", somme_total);
        printf("Durée : %ld ms\n", duree);

        return 0;
    }