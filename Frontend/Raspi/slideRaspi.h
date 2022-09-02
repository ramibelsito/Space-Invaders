/***************************************************************************//**
  @file     +Nombre del archivo (ej: template.h)+
  @brief    +Descripcion del archivo+
  @author   +Nombre del autor (ej: Salvador Allende)+
 ******************************************************************************/

#ifndef slideRaspi_H
#define slideRaspi_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "slide.h"
#include "joydrv.h"
#include "disdrv.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/



/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/



/*******************************************************************************
 * VARIABLE PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

// +ej: extern unsigned int anio_actual;+
extern int referenceMat [][MAX_ARR_X]; //Para poder verla

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief TODO: Desliza frase en LEDs
 * @param param1 string a deslizar en LEDs
 * @param param2 altura en la cual deslizar
 * @return nada
*/
void slideR (char string[], unsigned int altura);

/**
 * @brief TODO: Muestra en los LEDs la matriz de referencia
 * @param param1 string a deslizar en LEDs
 * @return nada
*/
void printMenu (int referencia [][MAX_ARR_X]);


/*******************************************************************************
 ******************************************************************************/

#endif // slideRaspi_H