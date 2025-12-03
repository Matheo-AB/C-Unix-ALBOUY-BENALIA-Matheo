#include "image.h"
#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[])
    {
        int width = 200;
        int height = 100;
        
        Image *img = image_create(width, height);

        if (img == NULL)
            {
                fprintf(stderr, "Erreur lors de la création de l'image.\n");
                return EXIT_FAILURE;
            }

        for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                    {
                        unsigned char blue_value = (unsigned char)((x * 255) / (width - 1));
                        unsigned char red = 0;
                        unsigned char green = 0;            
                        image_set_pixel(img, x, y, red, green, blue_value);
                    }
            }

        printf("Sauvegarde de l'image dans 'gradient.ppm'...\n");
        image_save_txt(img, "gradient.ppm");
        printf("Terminé.\n");

        return EXIT_SUCCESS;
    }