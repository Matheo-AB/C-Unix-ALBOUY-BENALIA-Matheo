#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INCREMENT 11111111
#define THREAD_COUNT 99

static long long compteur_global = 0;  // Variable partagée MODIFIABLE et MODIFIÉ

void* incrementeur_thread(void* arg) {
    for (int i = 0; i < INCREMENT; i++) {
        // TODO: Expliquer pourquoi, dans le détail, cette ligne qui pose problème
        compteur_global++;  // RACE CONDITION ICI !
    }
    return NULL;
}

int main(void) {
    printf("=== Compteur Dangereux ===\n");
        long long expected = INCREMENT*THREAD_COUNT;

    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_create(&threads[i], NULL, incrementeur_thread, NULL);

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);

    printf("Valeur attendue : %ld\n", expected);
    printf("Résultat final : %ld\n", compteur_global);
    printf("Différence : %ld\n", expected - compteur_global);

    return 0;
}