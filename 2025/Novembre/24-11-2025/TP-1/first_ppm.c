#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen("FirstPPM.ppm", "w");

    if (fp == NULL) {
        perror("Erreur d'ouverture du fichier");
        return EXIT_FAILURE;
    }
    
    fprintf(fp, "P3\n");

    const char *dimensions = " 3 2\n";
    fprintf(fp, "%s", dimensions); //Dimensions

    const char *max = "255\n";
    fprintf(fp, "%s", max);//Valeur maximale

    const char *ligne1 = " 255 0 0 0 255 0 0 0 255\n";
    fprintf(fp, "%s", ligne1);//Pixels
    
    const char *ligne2 = " 255 255 0 255 255 255 0 0 0\n";
    fprintf(fp, "%s", ligne2);// Première ligne & Deuxième ligne : rouge, vert, bleu & jaune, blanc, noir

    fclose(fp); // Fermeture du fichier
    printf("Image PPM créée avec succès !\n");

    return EXIT_SUCCESS;
}