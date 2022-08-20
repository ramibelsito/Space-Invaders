#include <stdio.h>
#include "disdrv.h"
#include "joydrv.h"

#define DISP_INIT_Y 12
#define THRESHOLD 40	//Límite a partir del cual se mueve el LED encendido
 
int main (void)
{
    joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear();
    dcoord_t pos = {DISP_MAX_X>>1 , DISP_INIT_Y};	//pos es la posición actual, empieza en el centro de la matriz
	dcoord_t npos = pos;							//npos es la próxima posición
    jcoord_t coord = {0,0};							//coordenadas medidas del joystick
    do
    {
        disp_update();
        joy_update();
		coord = joy_get_coord();
        if(coord.x > THRESHOLD && npos.x < DISP_MAX_X)
		{
			npos.x++;
		}
		if(coord.x < -THRESHOLD && npos.x > DISP_MIN)
		{
			npos.x--;
		}
        disp_write(pos,D_OFF);	//apaga la posición vieja en el buffer
		disp_write(npos,D_ON);	//enciende la posición nueva en el buffer
		pos = npos;				//actualiza la posición actual
		
	} while( joy_get_switch() == J_NOPRESS );	//termina si se presiona el switch
    
    return 0;
}