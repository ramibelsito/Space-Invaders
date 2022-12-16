#include <stdio.h>

#define n 100   //Cantidad máxima de aliens que pueden haber
#define m 15	//Cantidad máxima de trozos de barreras que pueden haber

typedef bool int;	//Parece que esto está mal escrito, CHEQUEAR!
#define TRUE 1
#define FALSE 0 

#define ALTURA 16	//Esto va a variar dependiendo del display (es para ver si la bala chocó contra el "piso")

/*Recibo el nombre del objeto contra el que colisionó y el índice que lo identifica.
Por ejemplo, ALIEN3 se carga en el struct como (int)('A'+3) */
#define OBJETO(X,Y) ( (int) ( (X)+(Y) ) )
#define ALIEN 'A'
#define BARRERA 'B'
#define MAPA 'M'
#define JUGADOR 'J'
#define PROYECTIL 'P'
//OBS: Es irrelevante el índice del jugador y el mapa es 0 si es techo y sino piso (como en el display)


//posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO

typedef struct bala
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int velocidad;		//Rapidez de la bala
	int sentido;		//La bala se dispara hacia arriba (jugador) o hacia abajo (aliens).
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (lo revisamos si está inactiva)
} bala_t;

typedef struct alien
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//Algunos aliens se desplazan más rápido que otros
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
} alien_t;

typedef struct barrera
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
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