/*No quiero perder mucho tiempo testeando esto porque el escalón que agrega es bastante trivial.
Básicamente, si funcionó intersection debería funcionar colisiona_hitbox. Voy a hacer una o dos
pruebas por las dudas nomás*/

//Funcionó

#include <stdio.h>

//Me devuelve 1 (verdadero) si los intervalos se intersecan. El par (x,y) está en el centro del hitbox.
int colisiona_hitbox(float x1, float y1, float ancho1, float alto1, float x2, float y2, float ancho2, float alto2);
//Recibo las coordenadas y dimensiones de dos objetos para ver si colisionan

//Me devuelve 1 (verdadero) si los intervalos se intersecan.
int intersection (float max1, float min1, float max2, float min2);


//Main de testeo
int main (void)
{
	float x1; float y1; float ancho1; float alto1; float x2; float y2; float ancho2; float alto2;

	//Tiene que dar 1 (colisiona)- FUNCIONA
	x1=500;y1=1500;ancho1=100;alto1=300;x2=400;y2=1600;ancho2=200;alto2=50;
	printf("%d\n", colisiona_hitbox(x1, y1, ancho1, alto1, x2, y2, ancho2, alto2) );

	//Tiene que dar 0 (no colisiona) - FUNCIONA
	x1=500;y1=1400;ancho1=100;alto1=300;x2=400;y2=1600;ancho2=200;alto2=50;
	printf("%d\n", colisiona_hitbox(x1, y1, ancho1, alto1, x2, y2, ancho2, alto2) );

	return 0;
}	//funcionó anachei



int colisiona_hitbox(float x1, float y1, float ancho1, float alto1, float x2, float y2, float ancho2, float alto2)
{	//Coloco la coordenada del objeto en el centro del hitbox!!!

	int colition_flag = 0;	//Si el los hitboxes de ambos objetos se superponen, entonces se activa.

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
}


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