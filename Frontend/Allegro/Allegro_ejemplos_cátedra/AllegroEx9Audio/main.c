#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
//Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm. 


int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    bool display_close = false;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to reserve samples!\n");
        return -1;
    }

    sample = al_load_sample("audio.wav");

    if (!sample) {
        printf("Audio clip sample not loaded!\n");
        return -1;
    }

    display = al_create_display(640, 480);

    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    event_queue = al_create_event_queue();

    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    //Loop the sample until the display closes.
    al_play_sample(sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    while (!display_close) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                display_close = true;
        }

    }

    al_uninstall_audio();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_sample(sample);
    return 0;
}
