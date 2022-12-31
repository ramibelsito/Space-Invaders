//#ifndef

#define n 100   //Cantidad máxima de aliens que pueden haber
#define m 15	//Cantidad máxima de barreras que pueden haber

//Esto va a variar dependiendo del display
#define Y_MAX 16
#define X_MAX 16

//Esto por las dudas, ni idea
#define TRUE 1
#define FALSE 0 


/*Recibo el nombre del objeto contra el que colisionó y el índice que lo identifica.
Por ejemplo, ALIEN3 se carga en el struct como (int)('A'+3) */
#define OBJETO(X,Y) ( (int) ( (X)+(Y) ) )
#define ALIEN 'A'
#define BARRERA 'B'
#define MAPA 'M'
#define JUGADOR 'J'
#define PROYECTIL 'P'
//OBS: Es irrelevante el índice del jugador, y el mapa es 0 si es techo y sino piso (como en el display)


//posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO

typedef struct bala
{
	float posicion[2];	//Coordenadas en el display, X e Y, respectivamente
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int velocidad;		//Rapidez de la bala
	int sentido;		//La bala se dispara hacia arriba (jugador) o hacia abajo (aliens).
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá vemos a qué le dio (lo revisamos si está inactiva)
} bala_t;

/*Evitamos desfazajes si el int colisiones está en el 
objeto contra el que la bala colisionó y no en la bala*/

typedef struct alien
{
	float posicion[2];	//Coordenadas en el display, X e Y, respectivamente
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//Algunos aliens se desplazan más rápido que otros
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} alien_t;

typedef struct barrera
{
	float posicion[2];	//Coordenadas en el display, X e Y, respectivamente
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} barrera_t;

typedef struct jugador
{
	float posicion[2];	//Coordenadas en el display, X e Y, respectivamente
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//A lo mejor varía en función del nivel
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} jugador_t;


/*
En cuanto a las "barreras compuestas" que había propuesto antes, llegué a la conclusión de que no suma
Estuve pensando que el hitbox puede variar sin problemas... XD
Es decir, podemos hacer un código que les asigne un png en función de su hitbox y listo, en vez de hacer
la cadena que por muy fachera y pro que pueda ser es complicársela completamente al pedo jajajajajaaj
Simplemente deberíamos ver el campo "hitbox" en cada caso (o sea, no tomar como que son siempre iguales)
pero eso es una pavada así que ya fue.
*/

/*
La verdad es que los structs son bastante similares. Quizás podríamos hacer uno solo y que
uno de los campos sea "objeto" y ahí decimos si es un alien, una bala, etc. Aunque la realidad
es que es más fácil escribir directamente alien_t en vez de if(cosa_t.objeto=alien){haceresto}
Bah qsy capaz no. Veremos si tenemos la necesidad de cambiarlo o no.
Yo por las dudas lo anoto
*/

//#endif


#include <stdio.h>


//Me devuelve 1 (verdadero) si los intervalos se intersecan.
int intersection (float max1, float min1, float max2, float min2);


//Me devuelve 1 (verdadero) si los hitbox se superponen. El par (x,y) está en el centro del hitbox.
int colisiona_hitbox(float x1, float y1, float ancho1, float alto1, float x2, float y2, float ancho2, float alto2);
//Recibo las coordenadas y dimensiones de dos objetos para ver si colisionan


//La j es el índice del objeto contra el que chocó la bala
//La i es el índice de la bala que estamos desactivando
//Impacto es el char en mayúscula del objeto contra el que chocó la bala. Les sugiero usar los defines (#define ALIEN 'A')
//posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO. También actualiza los datos de la colisión.
void desactivar_bala ( alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala, int i, char impacto, int j);


//Me devuelve 1 (verdadero) si la bala en cuestión impactó con otro objeto. Sino, 0 (falso).
int check_colisiones(alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala, int i);
//El índice i indica cuál bala está siendo chequeada. Lo demás son punteros a la info necesaria (ver nombres)


/*Mira todas las balas, una por una. Si están activas, chequea si están en colisión con otro objeto.
En caso de que sí, las desactiva y actualiza el campo "colisiones" de los objetos que colisionaron.*/
void check_bala (alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala);
//Tengo pensado que en un futuro también actualice la info de los objetos que pierden vida, etc al colisionar.
