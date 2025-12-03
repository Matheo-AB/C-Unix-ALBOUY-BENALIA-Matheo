#include "image.h"
#include <stdlib.h>
#include <string.h>

Image* image_create(int width, int height)
    {
        Image *img = (Image *)malloc(sizeof(Image));

        if(img ==0)
            return 0;

        img->width = width;
        (*img).height = height;
        img->pixels = (unsigned char*)malloc(width*height*3 * sizeof(unsigned char));
        return img;
    }

    void image_free(Image *img)
        {
            free(img->pixels);
            free (img);
        }

void image_set_pixel(Image *img, int x, int y, unsigned char r, unsigned char g, unsigned char b) {
    if (img != NULL && x >= 0 && x < img->width && y >= 0 && y < img->height) {
        int index = 0; // TODO trouvé le calcule
        img->pixels[index + 0] = r;
        img->pixels[index + 1] = g;
        img->pixels[index + 2] = b;
    }
}

void image_save_txt(Image *img, const char *filename) {
    if (img==0)
    return;
    FILE *fp = fopen("Gradient.ppm", "w");

    if (fp == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
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