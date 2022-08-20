/*
testJoy imprime las coordenadas del joystick. Termina cuando se presiona el switch.
*/

#include <stdio.h>
#include "joydrv.h"
#include "termlib.h"

int main(void)
{
	jcoord_t myCoords;
	joy_init();				//inicializo el joystick
	do
	{
		joy_update();							//primero actualizo las coordenadas medidas
		myCoords = joy_get_coord();				//luego las guardo en myCoords
		printf(CYAN_TEXT "(%4d, %4d)\n" , myCoords.x, myCoords.y);	
	} while (joy_get_switch() == J_NOPRESS);	//mientras no se presione el switch
	
	return 0;
}
