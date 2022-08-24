#include <stdio.h>
#include <allegro5/allegro.h> //NO OLVIDAR CONFIGURAR EL LINKER DESDE run-proyect configuration 

int main(void) {
    ALLEGRO_DISPLAY * display = NULL;

    if (!al_init()) { //Primera funcion a llamar antes de empezar a usar allegro.
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(640, 480); // Intenta crear display de 640x480 de fallar devuelve NULL
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)

    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla

    al_rest(5.0);

    al_destroy_display(display); //IMPORTANTE: Destruir recursor empleados

    //al_init es "destruido automaticamente" ver documentacion 
    return 0;
}
