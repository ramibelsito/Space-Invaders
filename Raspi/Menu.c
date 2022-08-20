#include <stdio.h>
#include "disdrv.h"
#include "joydrv.h"
#include <time.h>

#define N 16 //Tamano de la matriz de LEDs.
#define THRESHOLD 120 //Por lo que entendi viendo los codigos de los programas para probar los LEDs, es como la sensibilidad del analoguico.

void printMenu (int [][N]);//Hace los prints.
void startMenu (void);//Control del menu hasta que se aprete el analogico.
void waitFor (unsigned int);

/* El pIxEL aRt, a mano y global xd. Podemos cambiarlo*/
 int playMat [N][N] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
                         {0,0,0,0,1,1,1,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}};

    int hScoreMat [N][N] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
                            {0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0},
                            {0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
                            {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0}};

    int exitMat [N][N] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
                         {0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0},
                         {0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,0},
                         {0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0},
                         {0,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0},
                         {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
                         {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
                         {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
                         {0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0},
                         {0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0},
                         {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
                         {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                         {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0}};

int main (void)
{
    joy_init();				//inicializa el joystick
	disp_init();			//inicializa el display
	disp_clear();
    startMenu();
    return 0;                  
}

void startMenu (void) 
{
    dcoord_t pos = {DISP_MAX_X>>1 , DISP_MAX_X>>1};	//pos es la posición actual, empieza en el centro de la matriz
	dcoord_t npos = pos;							//npos es la próxima posición
    jcoord_t coord = {0,0};							//coordenadas medidas del joystick
    int position = 0;
    printMenu(playMat);

    do
    {   
        joy_update();
		coord = joy_get_coord();
        if(coord.x > THRESHOLD && npos.x < DISP_MAX_X)
		{
            switch (position)
            {
            case 0:
                disp_clear(); //Para que no se pinten los dibujos uno encima del otro.
                printMenu(hScoreMat);//Estoy en Play, entonces al mover hacia la derecha me muevo a la opcion de records.
                position++;
                break;
            case 1:
                disp_clear();
                printMenu(exitMat);//Estoy en records, entonces al mover hacia la derecha me muevo a la opcion de exit.
                position++;
                break;
            default: //Innecesario, lo deje por si lo usamos para algo.
                break;
            }
			coord.x = 0;	//Para mantener cierto control sobre las coordenadas. No se si es realmente necesario
		}
		if(coord.x < -THRESHOLD && npos.x > DISP_MIN)
		{
			switch (position)
            {
            case 1:
                disp_clear();
                printMenu(playMat); //Estoy en records, entonces al mover hacia la izq. me muevo a la opcion de play.
                position--;
                break;
            case 2:
                disp_clear();
                printMenu(hScoreMat); //Estoy en exit, entonces al mover hacia la izq. me muevo a la opcion de records.
                position--;
                break;
            default:
                break;
            }
			coord.x = 0;
		}
	} while( joy_get_switch() == J_NOPRESS );	//termina si se presiona el switch
    printf("%d\n", position);// Para chequear que al terminar el programa se elige la opcion que quiero (funciona :) )
    disp_clear();//Apago cuando termina el prog.
}
/*Lo de npos en la funcion esta (startMenu) esta re al pedo, pero no probe sacandolo, asique lo paso de la manera que me funciono.*/



void printMenu (int repMat [][N]) /*Un for que printea la matriz N x N que le pases (hecha asi nomas), funciona. El update esta
                                    al final pq si no hace update led por led y tarda bastante en hacerlo. (el update toma tiempo)*/
{
    int i, j;
    dcoord_t myPoint; 
    
    for (j = 0, myPoint.x = DISP_MIN; j < N; j++, myPoint.x++)
    {
        for (i = 0, myPoint.y = DISP_MIN; i < N; i++, myPoint.y++)
        {
            if (repMat [i][j] != 0)  
            {
                disp_write (myPoint, D_ON); //Prendo en el buffer.
            }
        }
    }
    disp_update(); //Lleva todo el buffer a los LEDs.
    //waitFor(2);

    
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}