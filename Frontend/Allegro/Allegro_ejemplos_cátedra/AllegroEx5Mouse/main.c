#include <stdio.h>
#include <allegro5/allegro.h>

#define FPS    60.0
#define SCREEN_W  640
#define SCREEN_H  480
#define CUADRADITO_SIZE 32


int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *cuadradito = NULL;

    bool redraw = false;
    bool do_exit = false;
    float cuadradito_x = SCREEN_W / 2.0 - CUADRADITO_SIZE / 2.0;
    float cuadradito_y = SCREEN_H / 2.0 - CUADRADITO_SIZE / 2.0;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    cuadradito = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);
    if (!cuadradito) {
        fprintf(stderr, "failed to create cuadradito bitmap!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }


    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(cuadradito);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(cuadradito); //Setea el bitmap a dibujar, por defecto se setea al ultimo display creado

    al_clear_to_color(al_map_rgb(255, 0, 255)); //Rellena el bitmap del cuadradito de violeta

    al_set_target_bitmap(al_get_backbuffer(display)); //Setea el bitmap a dibujar nuevamente en el display

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (!do_exit) // idem anterior
    {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
                redraw = true;

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)//Si se cierra el display o click de mouse cerrar
                do_exit = true;

            else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
                cuadradito_x = ev.mouse.x;
                cuadradito_y = ev.mouse.y;
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(cuadradito, cuadradito_x, cuadradito_y, 0);
            al_flip_display();
        }

    }

    al_destroy_bitmap(cuadradito);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
