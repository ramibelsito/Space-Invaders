/* 
 * File:   main.c
 * Author: r2d2
 *			Ramiro A. Merello (rmerello@itba.edu.ar)
 *
 * Created on June 4, 2016, 6:38 PM
 */

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

/*
        void al_draw_scaled_bitmap(ALLEGRO_BITMAP *bitmap, //Bitmap a dibujar 
   float sx, float sy, float sw, float sh,	//sx, sy punto del BITMAP a partir del cual se va a dibujar, podriamos querer 
                                                                                        //dibujar desde la mitad del dibujo, osea que no se vea una parte de la img.( generalmente se usa desde 0,0 )
                                                                                        //Sw , Sh : ancho y alto de la imagen a escalar
 
   float dx, float dy, float dw, float dh, //Dx , dy: Punto del display a partir del cual se dibujará 
   int flags);							   // Dw , dh : Width y Height (ancho y altura) de la imagen escalada

 */
int main(void) {
    ALLEGRO_DISPLAY *mi_display;
    ALLEGRO_BITMAP *display_background;

    if (!al_init()) //lo mismo que igual a 0
    {
        fprintf(stderr, "Unable to start allegro\n");
        return -1;
    } else if (!al_init_image_addon()) {
        fprintf(stderr, "Unable to start image addon \n"); //Igual que printf pero imprime al error std 
        al_uninstall_system();
        return -1;
    } else if (!(mi_display = al_create_display(800, 400))) {
        fprintf(stderr, "Unable to create display\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        return -1;
    } else if (!(display_background = al_load_bitmap("background.png"))) {
        fprintf(stderr, "Unable to load background\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(mi_display);
        return -1;
    }


    al_draw_scaled_bitmap(display_background,
            0, 0, al_get_bitmap_width(display_background), al_get_bitmap_height(display_background), //imagen
            0, 0, al_get_display_width(mi_display), al_get_display_height(mi_display), //a que tamaño queres que se dibuje la imagen
            0); //SIn flags podrian usar ALLEGRO_FLIP_HORIZONTAL o ALLEGRO_FLIP_VERTICAL muy utiles

    al_flip_display();
    al_rest(5.0); //Nos tomamos una siestita para poder ver la imagen

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(display_background,
            0, 0, al_get_bitmap_width(display_background), al_get_bitmap_height(display_background), //imagen
            0, 0, 500, 500, // TE LO DIBUJA DE 500 X500
            0); //SIn flags podrian usar ALLEGRO_FLIP_HORIZONTAL o ALLEGRO_FLIP_VERTICAL muy utiles

    al_flip_display();
    al_rest(5.0); //Nos tomamos una siestita para poder ver la imagen

    return (0);
}


#include <stdbool.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

/*
 *	Otra forma de inicializar allegro: util cuando hay muchas inicializaciones
 *	ya que al fallar una se va cayendo y destruyendo lo que inicializo. Sin embargo,
 *	resulta media confusa por el uso excesivo de indentacion/if anidados.
 *
 *	"(...). The answer to that is that if you need more than 
 *	3 levels of indentation, you're screwed anyway, and should fix
 *	your program." 
 *	-Linus Torvalds https://www.kernel.org/doc/Documentation/CodingStyle
 *	
 *   Usar a criterio y gusto de c/u.
 */
bool allegro_startup(void) {
    if (al_init()) {
        if (al_init_primitives_addon()) {
            if (al_install_keyboard()) {
                if (al_install_mouse()) {
                    if (al_init_image_addon()) {
                        al_init_font_addon(); //Void
                        if (al_init_ttf_addon()) {
                            if (al_install_audio()) {
                                if (al_init_acodec_addon()) {
                                    if (al_reserve_samples(1)) {
                                        return true;

                                    } else
                                        fprintf(stderr, "ERROR: Failed to reserve samples:(\n");
                                    //al_shutdown_acodec_addon(); Does not exist
                                } else
                                    fprintf(stderr, "ERROR: Failed to initialize acodec addon\n");
                                al_uninstall_audio();
                            } else
                                fprintf(stderr, "ERROR: Failed to install audio\n");
                            al_shutdown_ttf_addon();
                        } else
                            fprintf(stderr, "ERROR: Failed to initialize ttf addon\n");
                        al_shutdown_font_addon();
                        al_shutdown_image_addon();
                    } else
                        fprintf(stderr, "ERROR: Failed to initialize image addon\n");
                    al_uninstall_mouse();
                } else
                    fprintf(stderr, "ERROR: Failed to install mouse\n");
                al_uninstall_keyboard();
            } else
                fprintf(stderr, "ERROR: Failed to to install keyboard\n");
            al_shutdown_primitives_addon();
        } else
            fprintf(stderr, "ERROR: Failed to load primitives addon \n");
    } else
        fprintf(stderr, "ERROR: Failed to initialize allegro system\n");
    return false;
}
