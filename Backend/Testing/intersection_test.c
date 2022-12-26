//Ya probé todos los casos y fuciona bien.
//El último me había dado mal porque ingresé mal los datos jajajaj lo cambié y funcionó.

#include <stdio.h>

//Me devuelve 1 (verdadero) si los intervalos se intersecan.
int intersection (float max1, float min1, float max2, float min2); //(prototipo)

//Main de testeo
int main (void)
{
	float max1 = 1;
	float min1 = 1;
	float max2 = 1;
	float min2 = 1;

	//Sería una intersección en raspi (hitboxes de un píxel)
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Intervalo 2 es un subconjunto del intervalo 1
	max1 = 5; min1=1; max2=4; min2=2;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Intervalo 1 es un subconjunto del intervalo 2
	max1 = 4; min1=2; max2=5; min2=1;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Se intersecan de un lado
	max1 = 4; min1=2; max2=5; min2=3;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Se intersecan del otro
	max1 = 5; min1=3; max2=4; min2=2;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Se intersecan en un solo punto (de un lado)
	max1 = 6; min1=4; max2=4; min2=2;	//Si funcionó el de raspi, este debería funcionar también
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//Se intersecan en un solo punto (del otro lado)
	max1 = 4; min1=1; max2=6; min2=4;	//Si funcionó el de raspi, este debería funcionar también
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 1 - FUNCIONA

	//No se intersecan (de un lado)
	max1 = 4; min1=1; max2=10; min2=8;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 0 - FUNCIONA

	//No se intersecan (del otro lado)
	max1 = 10; min1=8; max2=4; min2=1;
	printf("%d\n", intersection(max1,min1,max2,min2) ); //Tiene que dar 0 - DIO MAL!! - *Corregi2*

	return 0;
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
}