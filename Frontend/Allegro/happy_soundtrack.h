#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_acodec.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
//Extensiones con acodec .wav, .flac, .ogg, .it, .mod, .s3m, .xm. 

int al_sound (char* path , float volume , float speed);
//Prende el flag si hubo un error. El string es la ruta del archivo. La velocidad normal es 1.0
