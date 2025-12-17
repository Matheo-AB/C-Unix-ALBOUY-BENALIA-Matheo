#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define INCREMENT 111111
#define THREAD_COUNT 100

static long long compteur_global = 0;  // Variable partagée MODIFIABLE et MODIFIÉ

void* incrementeur_thread(void* arg)
    {
        for (int i = 0; i < INCREMENT; i++)
            {
                // TODO: Expliquer pourquoi, dans le détail, cette ligne qui pose problème
                compteur_global++;  // RACE CONDITION ICI !
                /*La race condition apparait sur un nombre important d'itérations.
                Le compteur est modifié plusieurs fois en même temps donc + d'itérations = + de problèmes.
                Lorsque que le compteur fait une itération, au bout de n itérations, il y a un risque de décalage.
                Le compteur affichera 11 alors qu'on sera à 12 par exemple care une incrémentation se fait en plusieurs phases.*/
            }
        return NULL;
    }

int main(void)
    {
        printf("=== Compteur Dangereux ===\n");
            long long expected = INCREMENT*THREAD_COUNT;

        pthread_t threads[THREAD_COUNT];

        for (int i = 0; i < THREAD_COUNT; i++)
            pthread_create(&threads[i], NULL, incrementeur_thread, NULL);

        for (int i = 0; i < THREAD_COUNT; i++)
            pthread_join(threads[i], NULL);

        printf("Valeur attendue : %lld\n", expected);
        printf("Résultat final : %lld\n", compteur_global);
        printf("Différence : %lld\n", expected - compteur_global);

        return 0;
    }