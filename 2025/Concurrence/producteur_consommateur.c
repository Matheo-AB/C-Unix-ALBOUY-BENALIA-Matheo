#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TAILLE_BUFFER 5

// Ressources partagées 
static int buffer[TAILLE_BUFFER];
static int index_prod = 0;
static int index_cons = 0;

// Sémaphores 
static sem_t places_libres;
static sem_t elements_disponibles;
static sem_t mutex;               

// Fonctionsdu buffer 

void ajouter_buffer(int produit)
    {
        buffer[index_prod] = produit;
        index_prod = (index_prod + 1) %TAILLE_BUFFER;
    }

int retirer_buffer(void)
    {
        int produit = buffer[index_cons];
        index_cons = (index_cons + 1) %TAILLE_BUFFER;
        return produit;
    }

// Logique des Threads 
void* thread_producteur(void* arg)
    {
        int id = *(int*)arg;

        for (int i = 0; i < 10; i++)
            {
                int produit = id * 100 + i;
    
                sem_wait(&places_libres);
                sem_wait(&mutex);
    
                ajouter_buffer(produit);
                printf("[Producteur %d] Ajouté : %d (index_prod passe à %d)\n", id, produit, index_prod);
    
                sem_post(&mutex);
                sem_post(&elements_disponibles);
                usleep(rand() % 100000); // Simulation d'un temps de travail
            }
        printf(" [Producteur %d] terminé \n", id);
        return NULL;
    }

void* thread_consommateur(void* arg)
    {
        int id = *(int*)arg;

        for (int i = 0; i < 7; i++)
            {
                sem_wait(&elements_disponibles);
                sem_wait(&mutex);

                int produit = retirer_buffer();
                printf("[Consommateur %d] Retiré : %d (index_cons passe à %d)\n", id, produit, index_cons);
                
                sem_post(&mutex);
                sem_post(&places_libres);
                usleep(rand() % 200000);
            }
        printf(" [Consommateur %d] terminé \n", id);
        return NULL;
    }

int main(void)
    {
        srand(time(NULL));

        sem_init(&places_libres, 0, TAILLE_BUFFER);
        sem_init(&elements_disponibles, 0, 0);
        sem_init(&mutex, 0, 1);

        printf("=== Démarrage du système ===\n");
        printf("Config : 2 Producteurs (20 items) | 3 Consommateurs (21 items)\n\n");

        pthread_t producteurs[2];
        pthread_t consommateurs[3];
        int ids_prod[2] = {1, 2};
        int ids_cons[3] = {1, 2, 3};

        // Création des threads
        for (int i = 0; i < 2; i++) pthread_create(&producteurs[i], NULL, thread_producteur, &ids_prod[i]);
        for (int i = 0; i < 3; i++) pthread_create(&consommateurs[i], NULL, thread_consommateur, &ids_cons[i]);

        for (int i = 0; i < 2; i++) pthread_join(producteurs[i], NULL);
        sleep(2);

        printf("\n[Info] Le système a produit 20 objets pour 21 demandes.\n");
        printf("[Info] Annulation du consommateur bloqué...\n");

        for (int i = 0; i < 3; i++)
            {
                pthread_cancel(consommateurs[i]); 
            }

        sem_destroy(&places_libres);
        sem_destroy(&elements_disponibles);
        sem_destroy(&mutex);

        return 0;
    }