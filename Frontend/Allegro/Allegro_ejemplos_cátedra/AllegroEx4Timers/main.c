#include <stdio.h>
#include <allegro5/allegro.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <stdbool.h>

#define FPS    60.0 //¿Por que se uso double aca ? 
#define COLOR_INC_RATE 1
#define MAX_COLOR_VALUE 255


int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = false;
    bool display_close = false;
    unsigned int color = 0;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS); //crea el timer pero NO empieza a correr
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_timer(timer);
        return -1;
    }

    display = al_create_display(640, 480);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    al_start_timer(timer); //Recien aca EMPIEZA el timer

    while (!display_close) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER)
                redraw = true;

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                display_close = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(color, color, color));
            al_flip_display();

            color += COLOR_INC_RATE; //Incrementa el color
            color %= MAX_COLOR_VALUE; // Se queda con el resto de Max_color_rate. Ex color 11 y MAX 10 : 11%10 = 1
        }

    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
