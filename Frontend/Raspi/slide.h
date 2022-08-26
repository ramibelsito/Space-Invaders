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
#define MAX_HIGHT_LET 5
#define MAX_WIDTH_LET 4
#define LETTER_START 6

const int const matA [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, [6][8] = 1,
                                               [7][6] = 1,             [7][8] = 1,
                                               [8][6] = 1,             [8][8] = 1};

const int const matB [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1,  
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, 
                                               [7][6] = 1,             [7][8] = 1,
                                               [8][6] = 1, [8][6] = 1, [8][8] = 1};

const int const matC [MAX_ARR_X][MAX_ARR_Y] = {            [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             
                                               [6][6] = 1,            
                                               [7][6] = 1,             
                                                           [8][7] = 1, [8][8] = 1}; 

const int const matD [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1,
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1,             [6][8] = 1, 
                                               [7][6] = 1,             [7][8] = 1,             
                                               [8][6] = 1, [8][7] = 1};  
                                               
                                                                                                        

const int const matL [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1,  
                                               [5][6] = 1,             
                                               [6][6] = 1, 
                                               [7][6] = 1,             
                                               [8][6] = 1,  [8][7] = 1, [8][8] = 1};   





const int const matP [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, [6][8] = 1,
                                               [7][6] = 1,             
                                               [8][6] = 1}; 

const int const matY [MAX_ARR_X][MAX_ARR_Y] = { 
                                               [5][6] = 1,             [5][8] = 1,
                                                           [6][7] = 1, [6][8] = 1,
                                                           [7][7] = 1,             
                                               [8][6] = 1};                                                                                       

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
 * param param1 
 * param param2 
 * @return nada.
*/
void singleSlide (void);

/**
 * @brief TODO: Asigna matriz de letra a deslizar y desliza hhasta que aparezca completamente en pantalla.
 * @param param1 letra a deslizar
 * @param param2 altura de aparicion de la letra
 * @return nada.
*/

void letterSlide (char, unsigned int);

/**
 * @brief TODO: Utilizando las funciones anteriores, deslia la frase ingresada infinitamente
 * @param param1 frase a deslizar
 * @param param2 altura de aparicion de la frase
 * @return nada.
*/

void phraseSlide (char string[], unsigned int);

/*******************************************************************************
 ******************************************************************************/

#endif // SLIDE_H_