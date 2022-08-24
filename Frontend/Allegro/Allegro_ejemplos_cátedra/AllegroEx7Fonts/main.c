#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#define D_WIDTH  640
#define D_HEIGHT 480


int main(void) {
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_FONT * font = NULL;

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

    display = al_create_display(D_WIDTH, D_HEIGHT);

    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return -1;
    }

    font = al_load_ttf_font("disney.ttf", 36, 0); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 

    if (!font) {
        fprintf(stderr, "Could not load 'disney.ttf'.\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), D_WIDTH / 2, (D_HEIGHT / 4), ALLEGRO_ALIGN_CENTER, "Trivial por combinatoria");

    al_flip_display();

    al_rest(10.0);

    al_destroy_display(display);

    return 0;
}
