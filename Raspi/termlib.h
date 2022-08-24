/***************************************************************************//**
  @file     termlib.h
  @brief    kblib v3.0. Linux support for keyboard functions for getch and getche and kbhit 
            ansy.sys Like functions added
  @author   Daniel Jacoby
 ******************************************************************************/

#ifndef KBLIB_H
#define KBLIB_H


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define BUFFERED_ON  1
#define BUFFERED_OFF 0

// ============ Colored Text ===========

#define BLACK_TEXT      "\e[30;1m"
#define RED_TEXT		    "\e[31;1m"
#define GREEN_TEXT 		  "\e[32;1m"
#define YELLOW_TEXT 	  "\e[33;1m"
#define BLUE_TEXT 		  "\e[34;1m"
#define MAGENTA_TEXT 	  "\e[35;1m"
#define CYAN_TEXT 	    "\e[36;1m"
#define WHITE_TEXT 		  "\e[37m"

// How to use:  printf(RED_TEXT "Colored Text \n" WHITE_TEXT);


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Get a key without waiting for it (no echo) 
 * @return Next immediate character input 
*/
int getch(void);	    

/**
 * @brief Get a key without waiting for it (with echo) 
 * @return Next immediate character input 
*/
int getche(void);	   

/**
 * @brief Check if a key has been pressed at terminal  
 * @return 1 if a key is waiting in the keyboad buffer
*/
int kbhit(void);	         

/**
 * @brief Turns terminal line buffering on or off
*/
void changemode(int);       

//ansy.sys like

/**
 * @brief Set cursor position
 * @param x is column
 * @param y is row
*/
void gotoxy(int x, int y);  

/**
 * @brief Clear Screen 
*/
void clrscr(void);				      	


/*******************************************************************************
 ******************************************************************************/

#endif // KBLIB_H
