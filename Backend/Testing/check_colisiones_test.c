//Si funciona esto ya estamos ahí nomás

/*Recién se me acaba de ocurrir que en vez de copiar todo lo ya testeado en cada test,
podría compilar más de un .c para generar el ejecutable y listo bruh jajajaj */

// #Datazo: ctrl+A = seleccionar todo B)

//Arranco copiando la info del .h

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
	float posicion[2];	//Coordenadas en el display
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
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//Algunos aliens se desplazan más rápido que otros
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} alien_t;

typedef struct barrera
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} barrera_t;

typedef struct jugador
{
	float posicion[2];	//Coordenadas en el display
	float hitbox[2];	//Ancho y alto del objeto, respectivamente (tomamos hitboxes rectangulares)
	int vida;			//Cantidad de golpes que resiste
	int velocidad;		//A lo mejor varía en función del nivel
	void* dibujo;		//Dirección de memoria en la que se encuentra la imagen del objeto
	int colisiones;		//Acá informamos cuál fue la última colisión (ejemplo: bala i le pegó y todavía no le bajamos la vida)
} jugador_t;


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



int main (void)	//Main de testeo
{
	int i,j;	//Índices
	alien_t aliens[n];
	bala_t balas[n+1];	//El de los aliens más el del jugador.
	barrera_t barreras[m];
	jugador_t jugador;
	

	/*Voy a crear una bala y un alien que estén en colisión, pero en vez de mandar únicamente
	el alien en cuestión, voy a mandar todo el array y ver si la función lo encuentra y 
	hace todo lo que tiene que hacer.
	Después voy a hacer lo mismo con la otra función que falta chequear, a ver si también
	encuentra la bala por su propia cuenta.*/

	i=n-10; j=n-1;

	aliens[j].posicion[0]=500;	aliens[j].posicion[1]=1500;	//Uso el último alien para ver si mira todos
	aliens[j].hitbox[0]=100;	aliens[j].hitbox[1]=300;
	
	balas[i].posicion[0]=400;	balas[i].posicion[1]=1600;	//Uso una bala cualquiera
	balas[i].hitbox[0]=200;		balas[i].hitbox[1]=50;

	balas[i].dibujo=0x1111;		aliens[j].dibujo=0xafd;		//Les asigno un "dibujo" (porque están activos)
	
	printf("%d\n", check_colisiones(aliens, barreras, &jugador, balas, i) );				//Debería colisionar
	printf("%f  %f  %p\n", balas[i].posicion[0], balas[i].posicion[1], balas[i].dibujo);	//Debería estar desactivado
	printf("%f  %f  %p\n", aliens[j].posicion[0], aliens[j].posicion[1], aliens[j].dibujo);	//No debería estar desactivado

	//Chequeo que esté cargada la colisión
	if ( (balas[i].colisiones == OBJETO(ALIEN,j)) && (aliens[j].colisiones == OBJETO(PROYECTIL,i)) )
	{
		printf("Todo 0k. Diushtax wazouski 8 mil porciento tres estrellas el que no salta es holandés, francés, inglés, lo que se te cante\n");
	}	//Ayuda :(



	//Ahora chequeo que funcione si NO colisiona

	balas[i].colisiones = 0;	aliens[j].colisiones = 0;	//Limpio el campo de colisión

	aliens[j].posicion[0]=500;	aliens[j].posicion[1]=1400;	//Uso el último alien para ver si mira todos
	aliens[j].hitbox[0]=100;	aliens[j].hitbox[1]=300;
	
	balas[i].posicion[0]=400;	balas[i].posicion[1]=1600;	//Uso una bala cualquiera
	balas[i].hitbox[0]=200;		balas[i].hitbox[1]=50;

	balas[i].dibujo=0x1111;		aliens[j].dibujo=0xafd;		//Les asigno un "dibujo" (porque están activos)
	
	printf("%d\n", check_colisiones(aliens, barreras, &jugador, balas, i) );				//No debería colisionar
	printf("%f  %f  %p\n", balas[i].posicion[0], balas[i].posicion[1], balas[i].dibujo);	//No debería estar desactivado
	printf("%f  %f  %p\n", aliens[j].posicion[0], aliens[j].posicion[1], aliens[j].dibujo);	//No debería estar desactivado


	//Chequeo que siga limpio el campo de colisión (porque no colisionó con nada)
	if ( (balas[i].colisiones == 0) && (aliens[j].colisiones == 0) )
	{
		printf("Todo 0k. Diushtax wazouski 8 mil porciento tres estrellas el que no salta es holandés, francés, inglés, lo que se te cante\n");
	}	//Ayuda :(

	return 0;
}	//Llegó la hora de la verdad...		-	FUNCIONA TODO ANASHEEEEEEEEE	-


//Esto es una validación así que tiene más de un return. En concreto, uno para cada caso.
//Puedo impactar contra el final del mapa, contra un alien, contra una barrera, contra otra bala (proyectil) o contra el jugador
int check_colisiones(alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala, int i)
{
	int colition_flag = 0;	//Si el proyectil ya colisionó, entonces se activa y se concluye el análisis
	int j;					//Índice del objeto contra el que podría colisionar

	
	//Quiero rehacer esto porque en su momento no tuve en cuenta los hitboxes:

	/*El piso y el techo del mapa tienen "hitbox alto" = 1, y un "hitbox ancho" = X_MAX. 
	Las coordenadas del piso son ( X_MAX/2 ; Y_MAX ) y las del techo son ( X_MAX/2 ; 0 )
	Recordar siempre que en el display el eje Y apunta hacia abajo y NO hacia arriba */

	/*
	//Esto ya lo chequea pipe pero #programaciónALaDefensiva
	//Para este caso es más prolijo poner el return de una y no usar el colition_flag.
	switch ( (int)bala[i].posicion[1] )	//Chequeo su coordenada Y
	{//el casteo a int trunca? Si redondea entonces está mal. El switch no permite floats, una paja

		//La M de MAPA indica que impactó contra el final del espacio jugable.
		case ALTURA: j=1; desactivar_bala(bala, i, MAPA, j);return;	//La colisión "mapa 1" es chocar contra el piso
		case 0: j=0; desactivar_bala(bala, i, MAPA, j);		return;	//La colisión "mapa 0" es chocar contra el techo
		default: break;
	}	//Los índices respetan la convención de que nuestro display tiene el eje Y apuntando para abajo
		//Otra opción más "limpia" es analizar que el hitbox coincida con el límite del mapa
	*/	


	//Chequeo si colisionó contra un alien
	float pos_x = (bala[i]).posicion[0];	//Coordenadas de la bala
	float pos_y = (bala[i]).posicion[1];
	float alien_x;							//Coordenadas del alien
	float alien_y;

	float ancho_bala = bala[i].hitbox[0];	//Tamaño de la bala
	float alto_bala  = bala[i].hitbox[1];
	float ancho_alien;						//Tamaño del alien
	float alto_alien;		


	//Recordar que el alien n tiene índice j=n-1
	for ( j = 0 ; (j < n) && (colition_flag == 0) ; j++ )
	{	
		//Si el alien está activo, analizo:
		if (alien[j].dibujo != NULL )
		{
			//Determino la posición del alien en cuestión
			alien_x = alien[j].posicion[0];
			alien_y = alien[j].posicion[1];

			//Determino el tamaño del alien en cuestión
			ancho_alien = alien[j].hitbox[0];
			alto_alien  = alien[j].hitbox[1];
			//Si todos los aliens tuvieran el mismo tamaño, lo haría una sola vez al principio (mejor no).

			//Con las dimensiones de cada objeto, veo si sus hitboxes se intersecan
			if ( colisiona_hitbox(pos_x,pos_y,ancho_bala,alto_bala,alien_x,alien_y,ancho_alien,alto_alien) )
			{	//colisiona_hitbox devuelve 1 si hay colisión, y 0 si no la hay.
				
				colition_flag = 1;		//Aviso que ha habido una colisión.
				desactivar_bala(alien, barrera, jugador, bala, i, ALIEN, j);
				return colition_flag;	//No debe colisionar con más de un objeto, por eso concluye.
			}
		}
	}

	//Chequeo si colisionó contra una barrera 
	/*Acá podría tener en cuenta lo de encadenar barreras para hacer una barrera compuesta sin necesidad
	de hacer un struct nuevo para cada tipo de barrera (y así cambiarles el hitbox) 
	Eso le daría mucha versatilidad al código, más allá de si al final lo usamos o no*/
	/*
	En cuanto a las "barreras compuestas" que había propuesto antes, llegué a la conclusión de que no suma
	Estuve pensando que el hitbox puede variar sin problemas... XD
	Es decir, podemos hacer un código que les asigne un png en función de su hitbox y listo, en vez de hacer
	la cadena que por muy fachera y pro que pueda ser es complicársela completamente al pedo jajajajajaaj
	Simplemente deberíamos ver el campo "hitbox" en cada caso (o sea, no tomar como que son siempre iguales)
	pero eso es una pavada así que ya fue.
	*/

	//Chequeo si colisionó contra la nave nodriza
	/*Tengo que chequear el código de los chicos pero dudo que la nave nodriza pueda meterse dentro del
	arreglo de aliens porque tendría muchas excepciones y sería más fácil darle su propia identidad */
	//Aparentemente, la vamos a contar como un alien más, así que problema resuelto.

	//Chequeo si colisionó contra el jugador

	//Por último, chequeo si colisionó contra otro proyectil.
	/*En esta parte del código, dicho análisis es bastante similar al resto, la parte rara va a estar 
	a la hora de desactivarlas porque tengo que desactivar ambas. Podría hacer que la función 
	"desactivar bala" se llame a sí misma cuando le aviso que choqué contra otra bala, o sino podría
	llamarla yo desde acá dos veces, una para cada bala. Creo que es básicamente lo mismo. Habrá que
	ver cuál opción es la más general o versátil*/
	/*Al final ya contemplé eso en la función "desactivar_bala". Fue mucho más fácil de lo que en su
	momento creí que sería*/

	/*Recordar que no solo tengo que desactivar la bala si impacta contra algo, sino que también 
	tengo que bajarle la vida al objeto contra el que haya impactado para eventualmente también
	desactivarlo y/o sumarle puntos al jugador. Es lo único "distinto" que me falta contemplar,
	porque los otros tipos de colisiones son en escensia lo mismo. O sea, si ahora en el test me
	sale bien lo de chequear la colisión contra aliens, hacer el resto de casos va a ser casi
	copiar lo que ya haya hecho.*/
	//Recordar que bajarle la vida podría hacer que su imagen cambie. 
	//O sea, habría que actualizar el campo "dibujo"
	
	
	return colition_flag;	//Si no impactó contra nada, lo informo.
}




//De acá en adelante ya está todo testeado


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
		
	}

	//Si dos proyectiles chocaron entre sí, tengo que asegurarme de que ambos hayan sido desactivados.
	if ( bala[i].colisiones == OBJETO(PROYECTIL,j) )
	{
		bala[j].dibujo = NULL;
		bala[j].posicion[0] = 0;
		bala[j].posicion[1] = 0;
	}

	return;
}	//Esta función ya fue testeada


//Me devuelve 1 si los objetos se superponen (chocan). Ya fue testeada.
int colisiona_hitbox(float x1, float y1, float ancho1, float alto1, float x2, float y2, float ancho2, float alto2)
{	//Coloco la coordenada del objeto en el centro del hitbox!!!

	int colition_flag = 0;	//Si los hitboxes de ambos objetos se superponen, entonces se activa.

	//Busco los extremos en el intervalo Y de cada objeto para ver si se intersecan. 
	float max1 = y1+alto1/2;
	float min1 = y1-alto1/2;
	float max2 = y2+alto2/2;
	float min2 = y2-alto2/2;

	//Analizar primero los intervalos Y ahorra recursos, ya que es menos normal que se intersequen sin superponer los hitbox.

	colition_flag = intersection(max1,min1,max2,min2);	//Intersection me devuelve 1 (verdadero) si se intersecan.
	

	//Si los intervalos Y se intersecan, analizo los intervalos X.
	if (colition_flag)	
	{
		max1 = x1+ancho1/2;
		min1 = x1-ancho1/2;
		max2 = x2+ancho2/2;
		min2 = x2-ancho2/2;

		colition_flag = intersection(max1,min1,max2,min2);	//Me molesta tanto no poder poner tildes, que escribo en inglés JAJAJA
	}

	//Si ambos intervalos (X e Y) se intersecan, significa que sus hitboxes se superponen, entonces devuelvo 1. Sino, devuelvo 0.
	return colition_flag;

}	//Esta función ya fue testeada.


//Me devuelve 1 (verdadero) si los intervalos se intersecan.
int intersection (float max1, float min1, float max2, float min2)
{
	/*Que los intervalos se intersequen significa
	que uno está dentro del otro o que uno de sus
	extremos está encerrado por los del otro*/

	int intersection_flag = 0;
	
	//Les puse números romanos para que no piensen que están relacionadas al hitbox 1 o 2. Sólo son vars auxiliares.
	float auxi;
	float auxii;
	float auxiii;
	float auxvi;

	//El signo de la diferencia me indica de que lado está un punto respecto del otro.
	/*EJEMPLO: El 2 está a la izquierda del 3 porque 2-3 es negativo.
	El 3 está a la derecha del 2 porque 3-2 es positivo*/

	//max1 está encerrado por los extremos max2 y min2?
	auxi = max1-max2;
	auxii = max1-min2;
	//min1 está encerrado por los extremos max2 y min2?
	auxiii = min1-max2;
	auxvi = min1-min2;
	
	/*Observen que si min1 está entre max2 y min2 es porque max2 está entre min1 y max1,
	y así. Es decir, ya cubrimos todos los casos de intersección.
	Solo falta considerar el caso en que el intervalo 2 sea subconjunto del 1, que ya
	está contemplado directamente en el if en la parte de "auxvi*auxi<=0".
	Si no me creen, hagan un dibujo en una hoja jajajaja */

	//Si tienen distinto signo o si son cero es porque hubo intersección en al menos un punto.
	if ( (auxi*auxii<=0) || (auxiii*auxvi<=0) || (auxvi*auxi<=0) ) 
	{
		intersection_flag = 1; 
	}

	return intersection_flag;
}	//Ya está testeada 	