#include "slideRaspi.h"


void slideR (char string[], unsigned int altura)
{
    int i,j;

    for ( i = 0; string[i] != '\0'; i++)
    {
        for(j = 0; j <= MAX_WIDTH_LET; j++)
        {
            letterSlide(string[i], altura, j);//Copio j-esima columna de la matriz de la letra en la matriz de referencia.
            singleSlide(altura);//Deslizo hacia izquierda para continuar asignando.
            printMenu(referenceMat);//Copio en LEDs.
        }
        singleSlide(altura);//Termino una letra, dejo espacio para la siguiente.
    }

    for ( i = 0; i < MAX_ARR_X; i++)//Deslizo a la izquierda hasta que desaparezca la frase
    {
            singleSlide(0);//Desde altura que yo quiera
            printMenu(referenceMat);
    }
}

void printMenu (int repMat [][MAX_ARR_X]) /*Un for que printea la matriz N x N que le pases (hecha asi nomas), funciona. El update esta
                                    al final pq si no hace update led por led y tarda bastante en hacerlo. (el update toma tiempo)*/
{
    int i, j;
    dcoord_t myPoint; //Mis coordenadas del display
    
    for (j = 0, myPoint.x = DISP_MIN; j < MAX_ARR_X; j++, myPoint.x++)
    {
        for (i = 0, myPoint.y = DISP_MIN; i < MAX_ARR_X; i++, myPoint.y++)
        {
            if (repMat [i][j] == 1)  
            {
                disp_write (myPoint, D_ON); //Prendo en el buffer.
            }
            else
            {
                disp_write(myPoint,D_OFF);//Apago en el buffer
            }
        }
    }
    disp_update();//Paso datos del buffer al display.
}