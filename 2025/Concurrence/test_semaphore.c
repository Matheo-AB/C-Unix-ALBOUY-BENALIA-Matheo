#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TAILLE_BUFFER 5

// Partage 
int buffer[TAILLE_BUFFER];
int in = 0, out = 0;

sem_t places_libres;
sem_t elements_disponibles;
sem_t mutex;

// Fonctions du Buffer 
void ajouter(int item)
    {
        buffer[in] = item;
        in = (in + 1) % TAILLE_BUFFER;
    }

int retirer()
    {
        int item = buffer[out];
        out = (out + 1) % TAILLE_BUFFER;
        return item;
    }

// Logique des Threads 
typedef struct { int id; int nb_actions; } thread_args;

void* producteur(void* arg)
    {
        thread_args* a = (thread_args*)arg;
        for (int i = 0; i < a->nb_actions; i++)
            {
                int item = a->id * 100 + i;
                
                sem_wait(&places_libres);
                sem_wait(&mutex);
                
                ajouter(item);
                printf("[P %d] Produit: %d\n", a->id, item);
                
                sem_post(&mutex);
                sem_post(&elements_disponibles);        
                usleep(100000);
            }
        return NULL;
    }

void* consommateur(void* arg)
    {
        thread_args* a = (thread_args*)arg;
        for (int i = 0; i < a->nb_actions; i++)
            {
                sem_wait(&elements_disponibles);
                sem_wait(&mutex);
        
                int item = retirer();
                printf("\t[C %d] Consomme: %d\n", a->id, item);
                
                sem_post(&mutex);
                sem_post(&places_libres);        
                usleep(150000);
            }
        return NULL;
    }

// Gestion des Scénarios 
void executer_test(int nb_p, int items_p, int nb_c, int items_c)
    {
        printf("\n TEST: %d Prod (%d it.) vs %d Cons (%d it.) \n", nb_p, items_p, nb_c, items_c);
    
        // Reset sémaphores et indices
        in = 0; out = 0;
        sem_init(&places_libres, 0, TAILLE_BUFFER);
        sem_init(&elements_disponibles, 0, 0);
        sem_init(&mutex, 0, 1);

        pthread_t p_threads[nb_p], c_threads[nb_c];
        thread_args p_args[nb_p], c_args[nb_c];

        // Création
        for(int i=0; i<nb_p; i++) { p_args[i] = (thread_args){i+1, items_p}; pthread_create(&p_threads[i], NULL, producteur, &p_args[i]); }
        for(int i=0; i<nb_c; i++) { c_args[i] = (thread_args){i+1, items_c}; pthread_create(&c_threads[i], NULL, consommateur, &c_args[i]); }

        sleep(4); 
        printf("Fin du temps imparti pour ce scénario.\n");
    
        for(int i=0; i<nb_p; i++) pthread_cancel(p_threads[i]);
        for(int i=0; i<nb_c; i++) pthread_cancel(c_threads[i]);
        
        sem_destroy(&places_libres);
        sem_destroy(&elements_disponibles);
        sem_destroy(&mutex);
    }

int main()
    {
        // Scénario 1 : Équilibré (30 vs 30)
        executer_test(3, 10, 5, 6);

        // Scénario 2 : Producteurs plus rapides (50 produits vs 20 consommés)
        executer_test(5, 10, 2, 10);

        // Scénario 3 : Consommateurs plus rapides (50 produits vs 100 demandés)
        executer_test(1, 50, 10, 10);

        return 0;
    }