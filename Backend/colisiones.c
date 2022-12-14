#include "colisiones.h"
/*
Quick reminder:
Este thread solo se encarga de leer la info de los disparos que ya fue actualizada por 
otro thread y los desactiva si es necesario, informando contra qué colisionó. O sea,
acá no se realiza el desplazamiento de los objetos, solo se chequea si están colisio-
nando en un determinado instante.
De ser así, se desactiva la bala, se indica qué objetos colisionaron entre sí y
***actualiza la info de los objetos que pierden vida, etc al colisionar***
(eso último todavía no fue programado)
*/

//Recordar: posicion[2] = {0,0} y dibujo = NULL significa que está DESACTIVADO

/*Todavía no tengo muy claro cómo meter esto en un thread así que primero voy a centrarme en hacer 
que funcione la lógica de lo que quiero hacer y después lo voy a meter en un thread.*/

/*YA ESTÁ LISTO PARA SER TESTEADO EN UN THREAD*/
/*Por ahora sólo está escrito para chequear las colisiones de una bala contra un alien.
Como ya realiza todo el análisis, antes de generalizarlo a más casos, quiero chequear
que éste código funcione en un thread, ya que los otros casos son muy parecidos al ya
hecho.
Otro detalle es que no me percaté de hacer una distinción entre el origen de las balas,
o sea, una bala de un alien podría matar a otro alien. 
No creo que sea un problema si sólamente dispara la primer fila de aliens, ya que en ese
caso sería súper raro que se disparen entre sí y hasta podría ser una buena estrategia.
Tipo, pegarle siempre a una misma columna de aliens para que el más externo de dicha 
columna esté tan alto respecto al resto que termine disparándole a los demás aliens,
no sé si me explico.
Resumen, si solo dispara el alien más cercano al jugador en cada fila, entonces tupper,
tupper-fecto. Sino, lo cambio.*/

int main (void)
{
	//OBS: Si hay n aliens, hay n+1 balas. Una para cada alien más otra para el jugador.
	//Recordar que cada alien y cada jugador no puede tener más de una bala activa simultáneamente.
	alien_t aliens[n];
	bala_t balas[n+1];
	barrera_t barreras[m];
	jugador_t jugador;

	int play = 1;

	/*Ponele que esto es lo que va adentro del thread.
	Un while que depende de una variable que no controla.
	La variable play la debería controlar el que maneja
	el tema del menú y la pausa*/
	while (play) {check_bala(aliens, barreras, &jugador, balas);}

	return 0;
}



//hay n cantidad de aliens, por ende, n+1 cantidad de balas (tanto activas como inactivas)
//Necesita los punteros a la info de algunos de los objetos contra los que podría colisionar.
void check_bala (alien_t* alien, barrera_t* barrera, jugador_t* jugador, bala_t* bala)
{
	//Recordar que la bala n+1 tiene índice n en el arreglo (la primera tiene índice 0, no 1)
	for  ( int i = 0 ; i < n+1 ; i++ )
	{
		if ( (bala [i]).dibujo != NULL )
		{
			check_colisiones(alien, barrera, jugador, bala, i);
		}
	}

	return;
}



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

}	//Ya fue testeada con los aliens.


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