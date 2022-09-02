
#include "slide.h"

/*******************************************************************************
 * ROM CONST VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/
const int  matA [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, [6][8] = 1,
                                               [7][6] = 1,             [7][8] = 1,
                                               [8][6] = 1,             [8][8] = 1};

const int  matB [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1,  
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, 
                                               [7][6] = 1,             [7][8] = 1,
                                               [8][6] = 1, [8][6] = 1, [8][8] = 1};

const int  matC [MAX_ARR_X][MAX_ARR_Y] = {            [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             
                                               [6][6] = 1,            
                                               [7][6] = 1,             
                                                           [8][7] = 1, [8][8] = 1}; 

const int  matD [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1,
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1,             [6][8] = 1, 
                                               [7][6] = 1,             [7][8] = 1,             
                                               [8][6] = 1, [8][7] = 1};  
                                               
                                                                                                        

const int  matL [MAX_ARR_X][MAX_ARR_Y] = {     [4][6] = 1,  
                                               [5][6] = 1,             
                                               [6][6] = 1, 
                                               [7][6] = 1,             
                                               [8][6] = 1,  [8][7] = 1, [8][8] = 1};   





const int  matP [MAX_ARR_X][MAX_ARR_Y] = {[4][6] = 1, [4][7] = 1, [4][8] = 1, 
                                               [5][6] = 1,             [5][8] = 1,
                                               [6][6] = 1, [6][7] = 1, [6][8] = 1,
                                               [7][6] = 1,             
                                               [8][6] = 1}; 

const int  matY [MAX_ARR_X][MAX_ARR_Y] = { 
                                               [5][6] = 1,             [5][8] = 1,
                                                           [6][7] = 1, [6][8] = 1,
                                                           [7][7] = 1,             
                                               [8][6] = 1};
const int * detectLetter (char); //Util para la funcion que hace el deslizamiento. Mi idea (por ahora) es asignar una matriz a cada letra. 
                            //Entonces de alguna manera (imagino con un for jugando con los indices) formar frases.

//Funcion picante --> le paso un string con la palabra que quiero deslizar, y a que altura y utiliza las funciones anteriores para hacerlo.
//Imagino el armado de palabras definiendo un ancho para cada letra (el alto fijo en 5 leds) entonces usando esos indices

//Para las imagenes de play, settings, etc. definimos que se deslice hasta que quede centrado.


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
        case '\0':
        {
            printf("Terminador\n");
            return 0;
        }

		default:
		{
		    printf("Error.\n");
		    return 0;
		    break;
		}
    }
}

void singleSlide (unsigned int altura)
{
    int columnas, filas;
    
    for(columnas = 0; columnas < MAX_ARR_X; columnas++)//Deslizo la matriz actual hacia la izquierda.
    {
        for (filas = altura; filas < MAX_ARR_Y ; filas++)//menos para no pasarme de matriz. Y en la ultima columna pegamos lo q queremos.
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

int letterSlide (char letra, unsigned int altura, unsigned int columna)
{
    int filas, j;
    const int * letterMat = detectLetter(letra);// Asigno la matriz de la letra a deslizar
    if (columna > MAX_WIDTH_LET)
    {
        printf ("ERROR: Te excediste con la columna.\n");
        return -1;
    }
    else
    {
        j = LETTER_START + columna;// Le sumo la constante pq defini las matrices en cierta columna.
        for (filas = altura; filas < MAX_ARR_Y; filas++) //Agrego la primera parte de la letra al final de la columna, a la altura definida.
        {
            referenceMat[filas][15] = *(letterMat + (filas+4)*MAX_ARR_Y + j);    
        }
        return 0;
    }
}

/*void phraseSlide (char string[], unsigned int altura)
{
    int i,j;
    for ( i = 0; string[i] != '\0'; i++)
    {
        for(j = 0; j < MAX_WIDTH_LET; j++)
        {
            letterSlide(string[i], altura, j);//Copio j-esima columna de la matriz de la letra en la matriz de referencia.
            singleSlide(altura);//Deslizo hacia izquierda para continuar asignando.
        }
        singleSlide(altura);
    }
}*/

/*void phraseSlide (char string[], unsigned int altura)
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
}*/


