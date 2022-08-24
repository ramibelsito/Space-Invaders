#include <stdio.h>
#include "slide.h"

#define MAY_MIN(c)  (((c) >= 'A' && (c) <= 'Z') ? (c) - 'A' + 'a' : (c))

int testMat [MAX_ARR_X][MAX_ARR_Y] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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

void setHight (int [MAX_ARR_X][MAX_ARR_Y], int);//Quiero hacer que se pueda definir a que altura de la matriz pongo la letra o simbolo.
const int * detectLetter (char); //Util para la funcion que hace el deslizamiento. Mi idea (por ahora) es asignar una matriz a cada letra. 
                           //Entonces de alguna manera (imagino con un for jugando con los indices) formar frases.

//Funcion picante --> le paso un string con la palabra que quiero deslizar, y a que altura y utiliza las funciones anteriores para hacerlo.
//Imagino el armado de palabras definiendo un ancho para cada letra (el alto fijo en 5 leds) entonces usando esos indices

//Para las imagenes de play, settings, etc. definimos que se deslice hasta que quede centrado.


int main (void)
{
    const int * myMat;
    myMat = detectLetter('a');
    printf ("direc. matriz= %d\n puntero = %d\n",&matA[0][0], &*(myMat));
    return 0;
}

const int * detectLetter (char letter)
{
    letter = MAY_MIN(letter);
    switch (letter) //los casos van a ser las letras del abecedario, no se me ocurrio otra cosa que hacer ---> problema: tendriamos 26 
                    //matrices. Las definimos como const y no ocupan RAM si no me equivoco.
    {
    case 'a':
        return &matA[0][0]; //Si querria letra A, me devuelve puntero a matriz
        break;
    
    default:
        printf("Error.\n");
        break;
    }
}





/*int main (void)
{
    int * test;
    test = &testMat[0][0];
    int i,j;
    for (i = 0; i < MAX_ARR_X; i++)
    {
        for (j = 0; j < MAX_ARR_Y; j++)
        {
            printf("%d ", *(test + i * MAX_ARR_X + j));
        }
        printf("\n");
    }
    return 0;
}*/