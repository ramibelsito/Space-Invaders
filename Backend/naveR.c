#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "disdrv.h"
#include "joydrv.h"

#define N 16
#define  ONE_MS 1
#define UP	1
#define DOWN	-1
#define ON 1
#define OFF 0
#define DISPLAY_MAX_Y 16
#define VELOCIDAD   100000 //usleep trabaja con microsegundos. Entonces esto son 0.1 segundos.
#define DISP_INIT_Y 13
#define THRESHOLD 40
#define HITBOX 3
#define MAX_ARR_X 16
#define MAX_ARR_Y 16
#define ALIEN '1'
#define NAVE '2'
#define BALA '0'

//void waitFor (unsigned int);
void paint (dcoord_t coordenada, dlevel_t val, const int matriz[MAX_ARR_X][MAX_ARR_Y]);
void printObject (float coordenadas[2], dlevel_t valor, char objeto);
void startGame (void);
void printMenu (int [][N]);//Hace los prints.
int startMenu (void);//Control del menu hasta que se aprete el analogico.

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


typedef struct 
{
    float posicion[2];
    int active;
    float velocidad;
    int direccion;
    void * dibujo;

} bullet_t;

typedef struct 
{
    float posicion[2];
    int vida;
    float velocidad;
    void * dibujo;
    int disparar;
}aliens_t;

typedef struct 
{
    float posicion[2];
    float nposicion[2];
    void * dibujo;
    int vidas;

} player_t;

aliens_t aliens[N];
bullet_t balas[N + 1];//N aliens + 1 jugador
player_t jugador;

int stop = 1;

const int  matNAVE [MAX_ARR_X][MAX_ARR_Y] = { 
                                                            [0][1] = 1,
                                                [1][0] = 1, [1][1] = 1, [1][2] = 1};

void * updateBullets ()//Actualizacion de balas/
{
    int i; //indice
    //dcoord_t coordenadas;
    while (stop)
    {
        for (i = 0; i <= N; i++)//Actualizo TODAS, las balas. Aliens y jugador
        {
            if (balas[i].active == ON)
            {
                if (balas[i].direccion == UP )
                {
                    if (balas[i].posicion[1] > 0)
                    {
                        printObject (balas[i].posicion, OFF, BALA);//Funcion generica, en allegro la escriben como convenga.
                        balas[i].posicion[1] -= 1;//Actualizo bala
                        printObject(balas[i].posicion, ON, BALA);
                        //printf("coordenadas reales display = { %.0f, %.0f}\n", balas[i].posicion[0], balas[i].posicion[1]);
                        usleep(VELOCIDAD);
                    }
                    else//Desactivo la bala.
                    {
                        balas[i].active = OFF;
                        //printf("coordenadas a apagar display = { %.0f, %.0f}\n", balas[i].posicion[0], balas[i].posicion[1]);
                        printObject(balas[i].posicion, OFF, BALA);
                        balas[i].posicion[0] = 15;
                        balas[i].posicion[1] = 15;
                    }
                }
                else
                {
                    balas[i].posicion[1] += 1;//Actualizo bala
                   // waitFor(1);//Velocidad.
                    //printf ("Bala = {%.0f ; %.0f}", balas[i].posicion[0], balas[i].posicion[0]);

                }
            }
        }
    
    }
    pthread_exit(NULL);
}

int main (void)
{
    balas[N].direccion = UP;
    balas[N].active = OFF;
    joy_init();										//inicializa el joystick
	disp_init();									//inicializa el display
	disp_clear(); 
    int hola = 1;
    while (hola)
    {
        hola = startMenu();
    }
     
    return 0;
}

int startMenu (void) 
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
        usleep(VELOCIDAD/2);
       
	} while( joy_get_switch() == J_NOPRESS );	//termina si se presiona el switch
    printf("%d\n", position);// Para chequear que al terminar el programa se elige la opcion que quiero (funciona :) )
    switch (position)
    {
    case 0:
    {
        joy_update();
        stop = 1;
        usleep(VELOCIDAD/2);
        startGame();
        return 1;
        break;
    }
    case 1:
    {
        return 1;
        //mostrar high scores
        break;
    }
    case 2:
    {
        disp_clear();
        return 0;//Salgo;
        break;//Nada, termina el programa.
    }
    
    default:
        return 0;
        break;
    }
    disp_clear();//Apago cuando termina el prog.
}
/*Lo de npos en la funcion esta (startMenu) esta re al pedo, pero no probe sacandolo, asique lo paso de la manera que me funciono.*/

void startGame (void)
{
    dcoord_t pos = {DISP_MAX_X>>1 , DISP_INIT_Y};	//pos es la posición actual, empieza en el centro de la matriz
	dcoord_t npos = pos;							//npos es la próxima posición
    jcoord_t coord = {0,0};							//coordenadas medidas del joystick
    pthread_t mov_balas;
    disp_clear();
    pthread_create(&mov_balas, NULL, updateBullets, NULL);

    do
    {
        disp_update();
        joy_update();
		coord = joy_get_coord();
       
        if(coord.x > THRESHOLD && npos.x < (DISP_MAX_X - (HITBOX % 2)))//Si muevo a la derecha y no me choco con nd
		{
			npos.x++;//Prox posicion sera 1 a la derecha
		}
		if(coord.x < -THRESHOLD && npos.x > (DISP_MIN + (HITBOX % 2)))//Si muevo a la izq y no me choco con nd
		{
			npos.x--;//Prox posicion sera 1 a la izq
		}
        if(coord.y > THRESHOLD && npos.y > DISP_MIN)
		{
            if (balas[N].active == OFF)//Activo 1 bala a la vez
            {
                balas[N].active = ON;
                balas[N].posicion[0] = pos.x;
                balas[N].posicion[1] = pos.y;
            }
		}
        paint(pos, D_OFF, matNAVE);	//apaga la posición vieja en el buffer
		paint(npos, D_ON, matNAVE);	//enciende la posición nueva en el buffer
        disp_update(); //Constantemente lo actualizo.
		pos = npos;	//actualiza la posición actual	
        
        jugador.posicion[0] = pos.x;//Las guardo en el jugador;
        jugador.posicion[1] = pos.y;

	} while( joy_get_switch() == J_NOPRESS );	//termina si se presiona el switch
    stop = 0;
    pthread_join(mov_balas, NULL);//Vuelve el thread. Creo q ta bien asi.
    joy_update();
    disp_clear();
    usleep(VELOCIDAD/2);
}

void printMenu (int repMat [][N]) /*Un for que printea la matriz N x N que le pases (hecha asi nomas), funciona. El update esta
                                    al final pq si no hace update led por led y tarda bastante en hacerlo. (el update toma tiempo)*/
{
    int i = 0, j = 0;
    dcoord_t myPoint; 
    
    for (i = 0, myPoint.y = DISP_MIN; i < N; i++, myPoint.y++)
    {
        for (j = 0, myPoint.x = DISP_MIN; j < N; j++, myPoint.x++)
        {
            if (repMat [i][j] != 0)
            {
                disp_write (myPoint, D_ON); //Prendo en el buffer.
            }
        }
    }
     disp_update(); //Lleva todo el buffer a los LEDs.
    
}

void paint (dcoord_t coordenada, dlevel_t val, const int matriz[MAX_ARR_X][MAX_ARR_Y])//Coordenada es el punto, no el hitbox.
{
    int i, j;
    dcoord_t coords;
    coords.x = coordenada.x - (HITBOX % 2);
    coords.y = coordenada.y;

    for (i = 0; i < DISP_MAX_Y; i++)
    {
        for (j = 0; j < HITBOX; j++)
        {
            if (matriz[i][j] == ON)//La parte que quiero copiar
            {
               disp_write(coords, val);
            }
            coords.x++;
        }
        coords.x = coordenada.x - (HITBOX % 2);
        coords.y ++;
    }
}

void printObject (float posicion[2], dlevel_t valor, char objeto)
{
    dcoord_t coordenadas;
    coordenadas.x = posicion[0];
    coordenadas.y = posicion[1];
    switch (objeto)
    {
        case BALA:
        {
            disp_write (coordenadas, valor);
            break;
        }
        case ALIEN:
        {
            //paint (coordenadas, valor, matALIENS);
            break;
        }
        case NAVE:
        {
            paint(coordenadas, valor, matNAVE);
            break;
        }
    }
}

