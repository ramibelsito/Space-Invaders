/*
testDisp enciende todo el display de a un LED por vez
*/

#include <stdio.h>
#include "disdrv.h"
#include "termlib.h"

int main(void)
{
	
	dcoord_t myPoint = {};		//inicializa myPoint en (0,0). Recordemos que está arriba a la izquierda.
	disp_init();				//inicializa el display
	disp_clear();				//limpia todo el display
	for (myPoint.y = DISP_MIN; myPoint.y <= (DISP_MAX_Y); myPoint.y++)	//para cada coordenada en y...
	{
		for ( myPoint.x = DISP_MIN; myPoint.x <= (DISP_MAX_X) ; myPoint.x++)	//para cada coordenada en x...
		{
			disp_write(myPoint, D_ON);				//prende el LED en el buffer. Otra opción es: disp_write({i, j}, D_ON);
			printf(YELLOW_TEXT "(%2d,%2d) " , myPoint.x, myPoint.y);//imprime cuál LED fue encendido
			disp_update();							//ahora lo vemos en el display
		}
		printf("\n");
	}
	return 0;
}
