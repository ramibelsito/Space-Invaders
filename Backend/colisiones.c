//Acá voy a empezar a hacer las pruebas del thread de que chequea las balas
//Creo que es importante que la función sepa decir contra qué se colisióno e informárselo a quien la haya "iNvOcAdO"

/*
Quick reminder
Hay tres threads, uno que actualiza la info de los aliens
Otro que se encarga de que los aliens disparen y ACTUALIZA la info del disparo (y los activa si es necesario)
Y este. Este thread. XD 
Este thread solo se encarga de leer la info de los disparos que ya fue actualizada por el
otro thread y los desactiva si es necesario, informando contra qué colisionó
Nos falta que un thread actualice la info de las barreras. A lo mejor lo puedo meter acá.
*/

//posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO

#include "colisiones.h"

/*Todavía no tengo muy claro cómo meter esto en un thread así que primero voy a centrarme en hacer 
que funcione la lógica de lo que quiero hacer y después lo voy a meter en un thread.*/


/*TENGO UNA IDEA
Voy a hacer un arreglo con los punteros más importantes. 
Tipo, un arreglo que contenga el puntero al arreglo de balas, el puntero al arreglo
de aliens, el puntero al arreglo de barreras, etc. Esto sería útil para no estar
pasándole trescientas mil cosas a cada función todo el tiempo. Por ahora voy a tratar
de evitarlo igual, para no hacer tanto mamarracho, pero me lo anoto porque puede
llegar a ser útil.
*/
int main (void)	//main de testeo
{
	//OBS: Si hay n aliens, hay n+1 balas. Una para cada alien más otra para el jugador.
	//Recordar que cada alien y cada jugador no puede tener más de una bala activa simultáneamente.
	alien_t aliens[n];
	bala_t balas[n+1];
	barrera_t barreras[m];

	check_bala();

	return 0;
}

//hay n cantidad de aliens, por ende, n+1 cantidad de balas (tanto activas como inactivas)

void check_bala (const bala_t* bala, int n /*, barrera_t* barrera, int b */)
{
	//Recordar que la bala n+1 tiene índice n en el arreglo (la primera tiene índice 0, no 1)
	for  ( int i = 0 ; i < n+1 ; i++ )
	{
		if ( (bala [i]).dibujo != NULL )
		{
			check_colisiones(bala,i);
		}
	}

	return;
}


//Puedo impactar contra el final del mapa, contra un alien, contra una barrera, contra otra bala o contra el jugador
void check_colisiones(const bala_t* bala, int i)
{
	//Esto ya lo chequea pipe pero #programaciónALaDefensiva
	switch ( (bala[i]).posicion[1] )	//Chequeo su coordenada Y
	{	
		//La M de MAPA indica que impactó contra el final del espacio jugable.
		case ALTURA: desactivar_bala(bala, i, MAPA, 1); return;	//La colisión "mapa 1" es chocar contra el piso
		case 0: desactivar_bala(bala, i, MAPA, 0); return;		//La colisión "mapa 0" es chocar contra el techo
		default: break;
	}	//Lo hice así para respetar la convención de que nuestro display tiene el eje Y apuntando para abajo


	//Chequeo si colisionó contra un alien (ya terminé el diagrama de flujo)
	for 

	//Chequeo si colisionó contra una barrera 
	/*Acá podría tener en cuenta lo de encadenar barreras para hacer una barrera compuesta sin necesidad
	de hacer un struct nuevo para cada tipo de barrera (y así cambiarles el hitbox) 
	Eso le daría mucha versatilidad al código, más allá de si al final lo usamos o no*/

	//Chequeo si colisionó contra la nave nodriza
	/*Tengo que chequear el código de los chicos pero dudo que la nave nodriza pueda meterse dentro del
	arreglo de aliens porque tendría muchas excepciones y sería más fácil darle su propia identidad */

	//Por último, chequeo si colisionó contra otro proyectil.
	/*En esta parte del código, dicho análisis es bastante similar al resto, la parte rara va a estar 
	a la hora de desactivarlas porque tengo que desactivar ambas. Podría hacer que la función 
	"desactivar bala" se llame a sí misma cuando le aviso que choqué contra otra bala, o sino podría
	llamarla yo desde acá dos veces, una para cada bala. Creo que es básicamente lo mismo. Habrá que
	ver cuál opción es la más general o versátil*/

	/*Recordar que no solo tengo que desactivar la bala si impacta contra algo, sino que también 
	tengo que bajarle la vida al objeto contra el que haya impactado para eventualmente también
	desactivarlo y/o sumarle puntos al jugador*/

}


//Dibujo a NULL, coordenada (0,0) y actualizar el campo "colisiones"
//La j es el índice del objeto contra el que chocó
//La i es el índice de la bala o proyectil que estamos analizando (le digo proyectil así reservo la "b" para "barrera")
void desactivar_bala (const bala_t* bala, int i, char impacto, int j)
{
	//El campo
	switch (impacto)
	{
		case 'M': (bala[i]).colisiones = OBJETO(MAPA,j);		break;	//Impactó contra el final del Mapa
		case 'A': (bala[i]).colisiones = OBJETO(ALIEN,j);		break;	//Impactó contra un Alien
		case 'B': (bala[i]).colisiones = OBJETO(BARRERA,j);		break;	//Impactó contra una Barrera
		case 'J': (bala[i]).colisiones = OBJETO(JUGADOR,j);		break;	//Impactó contra otra el Jugador
		case 'P': (bala[i]).colisiones = OBJETO(PROYECTIL,j);	//La bala i impactó contra la jota y viceversa
				  (bala[j]).colisiones = OBJETO(PROYECTIL,i);	break;	//Impactó contra otro Proyectil
		default: break;
	}

	(bala[i]).dibujo = NULL;
	(bala[i]).posicion[0] = 0;
	(bala[i]).posicion[1] = 0;

	if ( *(bala[i]).colisiones = OBJETO(PROYECTIL,j) )
	{
		//desactivar también la otra bala (tengo que autorreferenciar a la función)
	}

	return;
}