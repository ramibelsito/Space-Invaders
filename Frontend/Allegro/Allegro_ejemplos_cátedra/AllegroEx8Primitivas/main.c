/* 
 * File:   main.c
 * Author: r2d2
 *
 * Created on February 30, 2016, 1:10 FM
 */

#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO

#define D_WIDTH  800
#define D_HEIGHT 600


int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

    display = al_create_display(D_WIDTH, D_HEIGHT);

    if (!display) {
        al_shutdown_primitives_addon();
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_clear_to_color(al_color_name("black"));
    al_flip_display();
    //Ir viendolo desde el manual, asi se acostumbran a leerlo


    al_clear_to_color(al_color_name("black"));
    al_draw_line(0, 0, D_WIDTH, D_HEIGHT, al_color_name("papayawhip"), 40.0);
    al_flip_display();

    al_rest(2.0);


    al_clear_to_color(al_color_name("black"));
    al_draw_circle(D_WIDTH / 2, D_HEIGHT / 2, 200.0, al_color_name("lavenderblush"), 10.0);
    al_flip_display();



    al_rest(2.0);

    al_clear_to_color(al_color_name("black"));
    al_draw_filled_circle(D_WIDTH / 2, D_HEIGHT / 2, 200.0, al_color_name("hotpink"));
    al_flip_display();


    al_rest(2.0);

    al_clear_to_color(al_color_name("black"));
    al_draw_rectangle(D_WIDTH / 2, D_HEIGHT / 2, D_WIDTH / 2 + 300, D_HEIGHT / 2 + 250, al_color_name("mediumspringgreen"), 20.0);
    al_flip_display();


    al_rest(2.0);

    al_clear_to_color(al_color_name("black"));
    al_draw_filled_rectangle(D_WIDTH / 2, D_HEIGHT / 2, D_WIDTH / 2 + 300, D_HEIGHT / 2 + 250, al_color_name("mediumspringgreen"));
    al_flip_display();


    al_rest(2.0);

    al_clear_to_color(al_color_name("black"));
    al_draw_ellipse(D_WIDTH / 2, D_HEIGHT / 2, 200.0, 160.0, al_color_name("lemonchiffon"), 10.0);
    al_flip_display();

    al_rest(2.0);


    al_destroy_display(display);
    al_shutdown_primitives_addon();
    return 0;
}

