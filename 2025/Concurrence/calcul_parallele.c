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
        long resultat;
    } args_t;

void* calcul_thread(void* arg)
    {
        // cette fonction est appelé via pthread_create
        // vous savez ce que représente @arg
        // vous notifié au compilateur "cette" address dois être considéré comme args_t
        args_t* args = (args_t*)arg;
        // vous pouvez accéder (read/write) a toutes les variables via `args->`
        args->resultat = (long)args->valeur * args->multiplicateur;

        return NULL;
    }

int main(void)
        {
            printf("=== Calcul Parallèle ===\n");
            struct timespec debut, fin;
            clock_gettime(CLOCK_MONOTONIC, &debut);

            
            pthread_t threads[TAILLE_DONNEES];
            
            //TODO Tableau des arguments
            args_t thread_args[TAILLE_DONNEES];

            //TODO Création des threads
            for (int i = 0; i < TAILLE_DONNEES; i++)
                {
                    // Préparation des données
                    thread_args[i].index = i;
                    thread_args[i].valeur = DONNEES[i];
                    thread_args[i].multiplicateur = MULTIPLICATEUR;

                    if (pthread_create(&threads[i], NULL, calcul_thread, (void*)&thread_args[i]) != 0)
                        {
                            perror("Erreur création thread");
                            return 1;
                        }
                }

            //TODO Attente des threads
            for (int i = 0; i < TAILLE_DONNEES; i++)
                {
                    pthread_join(threads[i], NULL);
                }

            // TODO: Agréger les résultats
            long somme_total = 0; 
            for (int i = 0; i < TAILLE_DONNEES; i++)
                {
                    somme_total += thread_args[i].resultat;
                }

            clock_gettime(CLOCK_MONOTONIC, &fin);
            
            long duree = (fin.tv_sec - debut.tv_sec) * 1000 + (fin.tv_nsec - debut.tv_nsec) / 1000000;

            printf("Résultat total : %ld\n", somme_total);
            printf("Durée : %ld ms\n", duree);

            return 0;
    }