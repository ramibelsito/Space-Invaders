//Fui probando con varios datos distintos y funciona bien.

/*Siempre dejo los tests guardados en el repo así si surge algún inconveniente podemos chequear qué fue
lo que testeamos en su momento, quizás hay algo que no se me ocurrió probar y acá ya queda registrado*/

#include <stdio.h>

#define n 100   //Cantidad máxima de aliens que pueden haber
#define m 15	//Cantidad máxima de barreras que pueden haber

//typedef bool int;	//Parece que esto está mal escrito, CHEQUEAR!
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

typedef struct bala
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int velocidad;		//Rapidez de la bala
	int sentido;		//La bala se dispara hacia arriba (jugador) o hacia abajo (aliens).
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá vemos a qué le dio (lo revisamos si está inactiva)
} bala_t;

/*Estoy pensando que evitaríamos desfazajes si el int colisiones estuviera
en la estructura contra la que la bala colsionó y no en la bala*/

typedef struct alien
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//Algunos aliens se desplazan más rápido que otros
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} alien_t;

typedef struct barrera
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} barrera_t;

typedef struct jugador
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Alto y ancho del objeto (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//A lo mejor varía en función del nivel
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} jugador_t;


void desactivar_bala ( alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala, int i, char impacto, int j);
//posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO. También carga los datos de la colisión.


//main de testeo:
int main (void)
{
	alien_t aliens[n];
	bala_t balas[n+1];	//El de los aliens más el del jugador.
	barrera_t barreras[m];
	jugador_t jugador;
	int i, j; char impacto;

	impacto = ALIEN;
	i=n;
	j=n-3;
	aliens[j].colisiones=0; balas[i].colisiones=0;	//Todavía no se cargó nada. La función les tiene que cargar algo.
	balas[i].posicion[0]=523; balas[i].posicion[1]=643; balas[i].dibujo=0x1111;
	aliens[j].posicion[0]=11; aliens[j].posicion[1]=33; aliens[j].dibujo=0xafd;
	//Las posiciones no tienen que tener sentido, es solo para ver si pasan de "algo" a "cero" (lo mismo para dibujo)

	desactivar_bala (aliens, barreras, &jugador, balas, i, impacto, j);

	printf("%f  %f  %p\n", balas[i].posicion[0], balas[i].posicion[1], balas[i].dibujo);	//Debería estar desactivado
	printf("%f  %f  %p\n", aliens[j].posicion[0], aliens[j].posicion[1], aliens[j].dibujo);	//No debería estar desactivado
	printf("%d\n%d\n", aliens[j].colisiones, balas[i].colisiones);	//Debería tener los datos de la colisión ya cargados

	//Hice esto para chequear que el numerito del printf de arriba sea el correcto
	if ( (balas[i].colisiones == OBJETO(ALIEN,j)) && (aliens[j].colisiones == OBJETO(PROYECTIL,i)) )
	{
		printf("Todo 0k. Diushtax wazouski 8 mil porciento tres estrellas el que no salta es holandés, francés, inglés, lo que se te cante\n");
	}	//Ayuda :(

	return 0;
}//Tengo un warning que no es relevante por ahora, por eso no le doy bola. Lo que quise probar sí funciona. 



//Desactivar un proyectil significa: dibujo a NULL, coordenada (0,0) y actualizar el campo "colisiones"
//La j es el índice del objeto contra el que chocó el proyectil
//La i es el índice de la bala o proyectil que estamos desactivando (le digo proyectil así reservo la "b" para "barrera")
void desactivar_bala ( alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala, int i, char impacto, int j)
{
	//Indico contra qué impactó...
	switch (impacto)
	{
		case 'M': bala[i].colisiones = OBJETO(MAPA,j);		break;	//Impactó contra el final del Mapa
		case 'A': bala[i].colisiones = OBJETO(ALIEN,j);		break;	//Impactó contra un Alien
		case 'B': bala[i].colisiones = OBJETO(BARRERA,j);	break;	//Impactó contra una Barrera
		case 'J': bala[i].colisiones = OBJETO(JUGADOR,j);	break;	//Impactó contra otra el Jugador
		case 'P': bala[i].colisiones = OBJETO(PROYECTIL,j);	//La bala i impactó contra la jota y viceversa
				  bala[i].colisiones = OBJETO(PROYECTIL,i);	break;	//Impactó contra otro Proyectil
		default: break;
	}

	//...y la desactivo.
	bala[i].dibujo = NULL;
	bala[i].posicion[0] = 0;
	bala[i].posicion[1] = 0;

	/* Podría hacer lo de switch impacto también para el objeto contra el que impactó. 
	Creo que así sería más fácil hacer el análisis posterior (bajarle vida, etc), ya 
	que sino se nos podría escapar algún análisis posterior al impacto por culpa de 
	que un thread se adelante al otro. Por ejemplo, si la bala se vuelve a disparar 
	casi inmediatamente después de haber sido desactivada, el thread que mira si una 
	bala desactivada tiene algo cargado en el campo de colisiones, no llegaría a verla 
	a tiempo. */
	//Decidido, lo voy a hacer:

	switch (impacto)
	{
		case 'A': alien[j].colisiones = OBJETO(PROYECTIL,i);	break;	//Impactó contra un Alien
		case 'B': barrera[j].colisiones = OBJETO(PROYECTIL,i);	break;	//Impactó contra una Barrera
		case 'J': jugador->colisiones = OBJETO(PROYECTIL,i);	break;	//Impactó contra otra el Jugador
		default: break;	
	}
	/*Ya pensé en mandar un puntero a void que diga la posición del objeto impactado (un p_impacto)
	para reducir la cantidad de argumentos recibidos pero es un quilombo al pedo. No es tan conve-
	niente como podría parecer en un principio*/

	//Si dos proyectiles chocaron entre sí, tengo que asegurarme de que ambos hayan sido desactivados.
	if ( bala[i].colisiones == OBJETO(PROYECTIL,j) )
	{
		bala[j].dibujo = NULL;
		bala[j].posicion[0] = 0;
		bala[j].posicion[1] = 0;
	}

	return;
}

//MUCHAAAAACHOOOOOOOS AHORA SÓLO QUEDA FESTEJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAR

/*
ALGUIEN: *toca un instrumento*
NADIE: ...
ABSOLUTAMENTE NADIE: ...
EL PIBE QUE NI SIQUIERA VE FÚTBOL: "La de muchachos te la sabés?"
*/