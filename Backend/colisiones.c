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
#include <stdio.h>

#define ALTURA 16	//Esto va a variar dependiendo del display (es para ver si la bala chocó contra el "piso")

typedef bool int; 

typedef struct bala
{
	float posicion[2];	//Coordenadas en el display
	int velocidad;		//Rapidez de la bala
	int direccion;		//Es la dirección en la que se desplaza, no la dirección de memoria.
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	char colisiones;	//Acá informamos cuál fue la última colisión (lo revisamos si está inactiva)
} bala_t;

typedef struct alien
{
	float posicion[2];	//Coordenadas en el display
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//Algunos aliens se desplazan más rápido que otros
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int hitbox;			//Tamaño del objeto (tener en cuenta para calcular las colisiones).
} alien_t;

typedef struct barrera
{
	float posicion[2];	//Coordenadas en el display
	int vida;			//Cantidad de golpes que resiste
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int hitbox;			//Tamaño del objeto (tener en cuenta para calcular las colisiones).
	void* cadena;		//Indica la posición de el siguiente "pedazo" que pertenece a la misma barrera. ***
} barrera_t;
/*
***	Por ejemplo, las barreras podrían estar compuestas por X cantidad de espacios. El "truco" es que no limitamos
	el tamaño de la barrera, sino todas las barreras del juego tendrían que tener el mismo hitbox.
	Imaginemos que de un nivel a otro queremos que las barreras se compongan de, digamos, 3 barreras "standard". 
	Para no hacer un embrollo con el valor de hitbox, podemos mantener el hitbox y armar una cadena de barreras
	para que se comporten como si fueran una sola. Entonces, el eslabón dos apunta al tres, el tres al uno y el 
	uno al 2 (en la variable "cadena"). Imaginemos que al eslabón 3 le pegan un tiro. Como son una misma barrera,
	el tiro debería bajarle la vida a toda la cadena, entonces miramos la variable "cadena". Si dicha variable es
	distinta de NULL, agarramos y copiamos la vida (y el dibujo si es que tenemos un dibujo distinto en función
	de la vida de la barrera) del eslabón 3 al 1 (porque en este caso, el 3 sería el último). Después vemos a quién
	apunta el 1 (apuntará al 2) y repetimos el proceso. 
	Llegará un punto en el que vamos a haber recorrido toda la cadena, habiendo así actualizado la vida de la barrera
	en su totalidad. La pregunta es, ¿cómo nos damos cuenta? Bueno, durante el proceso de actualizar la vida de la 
	barrera, notaremos que llegará un punto en el que la información que supuestamente debemos actualizar, ya está 
	actualizada. Es decir, si yo vengo saltando de eslabón en eslabón bajando la vida de 5 a 4 y me topo con que 
	la vida del siguiente eslabón ya no es 5, sino 4, significa que ya actualicé todos los eslabones.
	Así es como determinamos cuándo salir del bucle.
	anashei
*/
/*es posible que haya pensado todo eso al pedo porque se resuelve súper fácil de otra manera? Sí.
Estoy súper ilusionado con mi idea? También. Elijo creer... */

//Esta es la estructura de datos que devuelve como parámetro la función "check bala"
typedef struct colsiones
{

} colisiones_t;


/*Todavía no tengo muy claro cómo meter esto en un thread así que primero voy a centrarme en hacer 
que funcione la lógica de lo que quiero hacer y después lo voy a meter en un thread.*/

int main (void)	//main de testeo
{
	check_bala();
}

//hay n cantidad de aliens, por ende, n+1 cantidad de balas (tanto activas como inactivas)

void check_bala (const bala_t* bala, int n /*, barrera_t* barrera, int b*/)
{	
	//static colisiones_t estado [n];
	//Recordar que la bala n+1 tiene índice n en el arreglo (la primera tiene índice 0, no 1)
	for  ( int i = 0 ; i < n+1 ; i++ )
	{
		if ((bala [i]).dibujo != NULL)
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
	switch ( (bala[i]).posicion[1] )
	{	//Chequeo su coordenada Y
		case ALTURA: desactivar_bala(bala, i, 'M'); return;	//Si se terminó el mapa, destruyo la bala
		case 0: desactivar_bala(bala, i, 'M'); return;		//La M indica que impactó contra el final del mapa
		default: break;
	}

	


}


//Dibujo a NULL, coordenada (0,0) y actualizar el campo "colisiones"
void desactivar_bala (const bala_t* bala, int i, char impacto)
{
	switch impacto
	{
		case 'M': (bala[i]).colisiones ='M'; break;		//Impactó contra el final del Mapa
		case 'A': (bala[i]).colisiones ='A'; break;		//Impactó contra un Alien
		case 'B': (bala[i]).colisiones ='B'; break;		//Impactó contra una Barrera
		case 'P': (bala[i]).colisiones ='P'; break;		//Impactó contra otro Proyectil
		case 'J': (bala[i]).colisiones ='J'; break;		//Impactó contra otra el Jugador
		default: break;
	}

	(bala[i]).dibujo = NULL;
	(bala[i]).posicion[0] = 0;
	(bala[i]).posicion[1] = 0;

	if ((bala[i]).colisiones ='P')
	{
		//desactivar también la otra bala (tengo que autorreferenciar a la función)
	}

	return;
}