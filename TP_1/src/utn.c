/*
 * utn.c
 *
 *  Created on: 20 sep. 2021
 *      Author: usuario
 */
/*
 Enunciado
	Hacer una calculadora.Para ello el programa iniciará y contará con un menú de opciones:
	1. Ingresar 1er operando (A=x)
	2. Ingresar 2do operando (B=y)
	3. Calcular todas las operaciones
		a) Calcular la suma (A+B)
		b) Calcular la resta (A-B)
		c) Calcular la division (A/B)
		d) Calcular la multiplicacion (A*B)
		e) Calcular el factorial (A!)
	4. Informar resultados
		a) “El resultado de A+B es: r”
		b) “El resultado de A-B es: r”
		c) “El resultado de A/B es: r” o “No es posible dividir por cero”
		d) “El resultado de A*B es: r”
		e) “El factorial de A es: r1 y El factorial de B es: r2”
	5. Salir
• Todas las funciones matemáticas del menú se deberán realizar en una biblioteca aparte,
que contenga las funciones para realizar las cinco operaciones.
• En el menú deberán aparecer los valores actuales cargados en los operandos A y B
(donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado)
• Deberán contemplarse los casos de error (división por cero, etc)
• Documentar todas las funciones
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utn.h"

#define INTENTOS 5

static int getFloat(float* pResultado);
static int myGets(char* cadena, int longitud);
static int esNumericaFloat(char* cadena);

/**
* \brief Imprime el menu de opciones
* \param
* \return int entre 1 y 5 correspondiente a la opcion selecionada
*/
int imprimirMenu()
{
	int retorno;

		printf("\n1. Ingresar 1er operando (A=x)\n");
		printf("\n2. Ingresar 1er operando (B=y)\n");
		printf("\n3. Calcular todas las operaciones\n");
		printf("\n4. Informar resultados\n");
		printf("\n5. Salir\n");
		pedirNumeroIntconMaxyMin(&retorno, 1, 5, INTENTOS, "Ingrese la opcion deseada", "Ingrese opciones entre 1 y 5");
		return retorno;
}
//------------------------------------------------------
/**
* \brief pide un int, con minimos y max, intentos y mensajes
* \param recibe min, max, intento y mensajes a mostra y erro, puntero int de resultado
* \return Retorna -1 salio mal, 0 salio bien y 2 sin reintento
*/
int pedirNumeroIntconMaxyMin(int* px, int min, int max, int intentos, char* txt, char* txtError)
{
	int buffer;
	int retorno=-1;//No se pudieron validar parametros
	int i;
	int salidaScanf;
	if(px != NULL && min<max && intentos >=0 && txt != NULL && txtError != NULL)
	{
		for (i=0; i<=intentos; i++)
		{
			printf("\n%s\n",txt);
			__fpurge(stdin);
			salidaScanf=scanf("%d", &buffer);
			if (salidaScanf>0 && buffer>=min && buffer<=max)
			{
				retorno = 0; // OK cargo int
				*px=buffer;
				break;
			}
			else
			{
				retorno=-2; //Sin intento
				printf("%s\n",txtError);
			}
		}
	}
	return retorno;
}
//------------------------------------------------------
/**
 * \brief Solicita un numero al usuario, leuego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int pedirNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, int reintentos)
{
	float bufferFloat;
	int retorno = -1;
	while(reintentos>0)
	{
		__fpurge(stdin);
		reintentos--;
		printf("\n%s\n",mensaje);
		if(getFloat(&bufferFloat) == 0)
		{
			*pResultado = bufferFloat;
			retorno = 0;
			break;
		}
		printf("\n%s\n",mensajeError);
	}
	return retorno;
}
/**
 * \brief Verifica si la cadena ingresada es numerica
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
*
*/
static int getFloat(float* pResultado)
{
	int retorno=-1;
	char buffer[64];
	if(pResultado != NULL)
	{
		if(myGets(buffer,sizeof(buffer))==0 && (esNumericaFloat(buffer))==0)
			{
			*pResultado = atof(buffer);
			retorno = 0;
			}
	}
	return retorno;
}
/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
*
*/
static int myGets(char* cadena, int longitud)
{
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		__fpurge(stdin);
		if(cadena[strlen(cadena)-1] == '\n')
			{
			cadena[strlen(cadena)-1] = '\0';
			}
		return 0;
	}
	return -1;
}
/**
* \brief Verifica si la cadena ingresada es numerica
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 0 (vardadero) si la cadena es numerica y -1 (falso) si no lo es
*/
static int esNumericaFloat(char* cadena)
{
	int i=0;
	int retorno = 0;
	if(cadena != NULL && strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
			{
				if(cadena[i] < 48 || cadena[i] > 57)
					{
					if(cadena[i]==46)
						{

						}else
						{
							retorno = -1;
							break;
						}
					}
				i++;
			}
	}
	return retorno;
}
//------------------------------------------------------
/**
* \brief suama dos float
* \param recibe dos float resultado por puntero
* \return return Retorna 0 (salio bien) y -1 (salio mal)
*/
int sumaFloat(float* z, float x, float y)
{
	int estado=-1;
	if(z !=NULL)
	{
		*z=x+y;
		estado=0;
	}
	return estado;
}
//------------------------------------------------------
/**
* \brief resta dos float
* \param recibe dos float resultado por puntero
* \return return Retorna 0 (salio bien) y -1 (salio mal)
*/
int restaFloat(float* z, float x, float y)
{
	int estado=-1;
	if(z != NULL)
	{
		*z=x-y;
		estado=0;
	}
	return estado;
}
//------------------------------------------------------
/**
* \brief multipluica dos float
* \param recibe dos float resultado por puntero
* \return return Retorna 0 (salio bien) y -1 (salio mal)
*/
int multiplicacionFloat(float* z, float x, float y)
{
	int estado=-1;
	if(z != NULL)
	{
		*z=x*y;
		estado=0;
	}
	return estado;
}
//------------------------------------------------------
/**
* \brief Divide dos numero float y verifica no dividir por 0
* \param recibe dos float, puntero float de resultado
* \return Retorna 1 (salio bien) y 0 (salio mal) No dividir por 0
*/
int dividirFloat(float* z, float x,float y)
{
	int estado = -1;
	if(y !=0 && z!=NULL)
	{
		*z =x / y;
		estado=0;
	}
	/*
	else
	{
		printf("\nError: División por cero\n");
	}
	*/
	return estado;
}
//------------------------------------------------------
/**
* \brief Calcula el factorial de numero naturales igual o mayor a 0
* \param recibe natural valor del factorial por puntero
* \return return Retorna 0 (salio bien) y -1 (salio mal)
*/
int factorial(int* result, int valor)
{
	int estado=-1;
		if (valor > 0)
		{
			if(valor==1 || valor==0)
							{
							*result = 1;
							estado=0;
							}else
							{
								*result=valor*(valor-1);
								while(valor>2)
									{
									valor--;
									*result=*result*(valor-1);
									}
							estado=0;
							}
		}
	return estado;
}
//------------------------------------------------------
