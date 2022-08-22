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



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define MAX_ARR_X 16
#define MAX_ARR_Y 16

const int matA [MAX_ARR_X][MAX_ARR_Y];


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: completar descripcion
 * @param param1 String a deslizar.
 * @param param2 Altura que quiera deslizar. De menor a mayor (0, 1 o 2).
 * @return Devuelve 1 si se realizo sin errores, 0 si hay un error.
*/
// +ej: char lcd_goto (int fil, int col);+

int slidePhrase (char string [], int hight);

/*******************************************************************************
 ******************************************************************************/

#endif // SLIDE_H_