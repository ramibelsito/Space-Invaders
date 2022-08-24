#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <stdbool.h>


int main(void) {
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    bool close_display = false; //explicar bool tipo de dato
    int i = 0;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    //queue == cola/fila en ingles 
    event_queue = al_create_event_queue(); //Allegro usa cola eventos, como las colas del super pero sin comida :( (por orden de llegada)
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        return -1;
    }

    display = al_create_display(640, 480); //Por que conviene crear el display ultimo???
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_event_queue(event_queue);
        return -1;
    }

    //Registra el display a la cola de eventos, los eventos del display se iran guardando en la cola 
    // a medida que vayan sucediendo 
    al_register_event_source(event_queue, al_get_display_event_source(display));

    //void al_clear_to_color(ALLEGRO_COLOR color) , ALLEGRO_COLOR al_map_rgb( unsigned char r, unsigned char g, unsigned char b)
    al_clear_to_color(al_color_name("hotpink"));
    al_flip_display();

    while (!close_display) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                close_display = true;
        }
    }

    al_destroy_display(display); //Destruir recursor empleados 
    al_destroy_event_queue(event_queue);
    //Recordar al init es "destruido" automaticamente 
    return 0;
}
