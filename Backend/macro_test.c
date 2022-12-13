#include <stdio.h>

#define OBJETO(X,Y) ( (int) ( (X)+(Y) ) )

#define PROYECTIL 'P'	//Las balas pueden chocar entre sí
#define ALIEN 'A'
#define BARRERA 'B'
#define MAPA 'M'
#define JUGADOR 'J'
//OBS: El jugador siempre tiene índice cero y el mapa es 0 si es techo y sino piso (como en el display)

int main (void) 
{
	printf("%d\n", OBJETO(MAPA,20));
	return 0;
}