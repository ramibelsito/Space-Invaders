/***************************************************************************//**
  @file     slide.h (ej: template.h)+
  @brief    funciones para tener texto deslizante.
  @author   Felipe Mendía
 ******************************************************************************/

#ifndef SLIDE_H_
#define SLIDE_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_ARR_X 16
#define MAX_ARR_Y 16
#define MAX_HIGHT_LET 5
#define MAX_WIDTH_LET 3
#define LETTER_START 6
#define MAY_MIN(c)  (((c) >= 'A' && (c) <= 'Z') ? (c) - 'A' + 'a' : (c))
                                                                                       

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/



int referenceMat [MAX_ARR_X][MAX_ARR_Y]; /*Global para que lo vean en todos lados. Pues todas las funciones trabajan sobre esta.
                                            Para su uso en allegro o raspi, se copia lo q le paso a esta matriz*/


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: "desliza" la matriz de referencia en una posicion hacia la izquierda.
 * @param param1 altura desde la cual desliza todo. Osea, 0 desde ariba de todo, 15 solo la ultima fila.
 * param param2 
 * @return nada.
*/
void singleSlide (unsigned int altura);// por ahora solo altura, desp le agrego el "piso" asi fijamos la franja que queramos deslizar.

/**
 * @brief TODO: Asigna matriz de letra a deslizar y desliza la columna (de 0 a 3) a meter en el "ciclo" de deslizamiento.
 * @param param1 letra a deslizar
 * @param param2 altura de aparicion de la letra
 * @return -1 si hubo un error (sea pasar mal los parametros o interno).
*/
int letterSlide (char letra, unsigned int altura, unsigned int columna);




/*******************************************************************************
 ******************************************************************************/

#endif // SLIDE_H