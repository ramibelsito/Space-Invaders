#include <stdio.h>
#include "slide.h"

#define MAY_MIN(c)  (((c) >= 'A' && (c) <= 'Z') ? (c) - 'A' + 'a' : (c))

const int * detectLetter (char); //Util para la funcion que hace el deslizamiento. Mi idea (por ahora) es asignar una matriz a cada letra. 
                            //Entonces de alguna manera (imagino con un for jugando con los indices) formar frases.

//Funcion picante --> le paso un string con la palabra que quiero deslizar, y a que altura y utiliza las funciones anteriores para hacerlo.
//Imagino el armado de palabras definiendo un ancho para cada letra (el alto fijo en 5 leds) entonces usando esos indices

//Para las imagenes de play, settings, etc. definimos que se deslice hasta que quede centrado.


int main (void)//Main de testeo.
{
    int i,j;
    for (i = 0; i < MAX_ARR_X; i++)
    {
        for (j = 0; j < MAX_ARR_Y; j++)
        {
            printf("%d ", referenceMat[i][j]);
        }
        printf("\n");
    }
    phraseSlide ("play", 0);
    
    //printf("\n"); printf("\n"); printf("\n");

    /*for (i = 0; i < MAX_ARR_X; i++)
    {
        for (j = 0; j < MAX_ARR_Y; j++)
        {
            printf("%d ", referenceMat[i][j]);
        }
        printf("\n");
    }*/
    return 0;
}

const int * detectLetter (char letter)
{
    letter = MAY_MIN(letter);
    switch (letter) //los casos van a ser las letras del abecedario, no se me ocurrio otra cosa que hacer ---> problema: tendriamos 26 
    {               //matrices. Las definimos como const y no ocupan RAM si no me equivoco.
		case 'a':
		{
		    return &matA[0][0]; //Si querria letra A, me devuelve puntero a matriz
		    break;
		}
		case 'p':
		{
		    return &matP[0][0]; //Si querria letra A, me devuelve puntero a matriz
		    break;
		}
		case 'l':
		{
		    return &matL[0][0]; //Si querria letra A, me devuelve puntero a matriz
		    break;
		}
		case 'y':
		{
		    return &matY[0][0]; //Si querria letra A, me devuelve puntero a matriz
		    break;
		}

		default:
		{
		    printf("Error.\n");
		    return 0;
		    break;
		}
    }
}

void singleSlide (void)
{
    int i, j, columnas, filas;
    for(columnas = 0; columnas < MAX_ARR_X; columnas++)//Deslizo la matriz actual hacia la izquierda.
    {
        for (filas = 0; filas < MAX_ARR_Y ; filas++)//menos para no pasarme de matriz. Y en la ultima columna pegamos lo q queremos.
        {
            if (columnas == 15)
            {
                referenceMat[filas][columnas] = 0;//La ultima la borra para q no queden valores basura.
            }
            else
            {
                referenceMat[filas][columnas] = referenceMat[filas][columnas+1]; //Paso la columna i+1 a la columna i.
            }
        }
    }
}

void letterSlide (char letra, unsigned int altura)
{
    int filas, columnas, j;
    const int * letterMat = detectLetter(letra);// Asigno la matriz de la letra a deslizar

    for(j = LETTER_START; j < MAX_WIDTH_LET + LETTER_START; j++)// Que no sobrepase el ancho.
    {
        for (filas = altura; filas < MAX_ARR_Y; filas++) //Agrego la primera parte de la letra al final de la columna, a la altura definida.
        {
            
            referenceMat[filas][15] = *(letterMat + filas*MAX_ARR_Y + j);
            
        }
        singleSlide(); //Luego de completar una columna de la letra, deslizo todo para luego escribir la siguiente.
    }    
}

void phraseSlide (char string[], unsigned int altura)
{
   int i; //Contadores

   	for(i = 0; string[i] != '\0'; i++) //Hasta que termine string
   	{
   		letterSlide(string[i], altura);//Deslizo el caracter.
   	}

   	i = 0; //Reciclo contador

   	while( i++ < MAX_ARR_X)
   	{
   		singleSlide();
   	}
}
