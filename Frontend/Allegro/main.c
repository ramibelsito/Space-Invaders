#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "happy_soundtrack.h"

#define D_HEIGHT 1080
#define D_WIDTH 1920
int main(void)
{
    //Buenas, soy juani agregando un llamado a la función al_sounds para ver si rompí todo o no
    float velDeReprod = 1.0 , volumen = 10;	//Clases grabadas de perotti be like
    

    if (al_sound("audio.wav" , volumen , velDeReprod))
    {
        printf ("Por lo tanto, no se ha reproducido el audio solicitado.\n");
        return -1;
    }
    /*La idea es que después los audios estén en su respectiva carpeta en el backend
    pero esta vez metí el audio de muestra acá nomás para saber si funcionaba*/


    ALLEGRO_DISPLAY * display = NULL;
    if (!al_init()) 
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(D_WIDTH, D_HEIGHT);
    if (!display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }
    if (!al_init_image_addon())
    {
        fprintf(stderr, "failed to initialize image addon!\n");
        return -1;
    }
    ALLEGRO_BITMAP *PlayButton = al_load_bitmap("PlayButton.png");
    ALLEGRO_BITMAP *CrownButton = al_load_bitmap("CrownButton.png");
    al_clear_to_color(al_color_name("black"));
    
    al_draw_bitmap(PlayButton, D_WIDTH/6, D_HEIGHT/8, NULL);
    al_draw_bitmap(CrownButton, 0, D_HEIGHT/5, NULL);
    al_flip_display();
    al_rest(10);
    al_destroy_display(display);
    al_destroy_bitmap(PlayButton);
    al_destroy_bitmap(CrownButton);
    return 0;
}