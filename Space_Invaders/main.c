#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define D_HEIGHT 1080
#define D_WIDTH 1920
int main(void)
{
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