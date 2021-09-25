/*  utn.c
 *  Created on: 20 sep. 2021
 *  Author: Tejeda Roberto
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utn.h"

#define INTENTOS 5

static int myGets(char* cadena, int longitud);
static int esNumericaFloat(char* cadena);
static int esNumericaInt(char* cadena);
//====================================================================================
/**
* \brief Imprime el menu de opciones
* \param valor actual de los operadores
* \return int entre 1 y 5 correspondiente a la opcion selecionada
*/
int imprimirMenu(float x, float y)
{
	int retorno;
		printf("\n\n===================================\n");
		printf("\n1. Ingresar 1er operando (A=%.4f)\n",x);
		printf("\n2. Ingresar 1er operando (B=%.4f)\n",y);
		printf("\n3. Calcular todas las operaciones\n");
		printf("\n4. Informar resultados\n");
		printf("\n5. Salir\n");
		printf("\n===================================\n\n");
		__fpurge(stdin);
		pedirInt(&retorno, "Ingrese la opcion deseada", "Ingrese opciones entre 1 y 5", 1, 5, INTENTOS);

		return retorno;
}
//=======================================================================================
/**
 * \brief Solicita un numero float al usuario, leuego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int pedirFloat(float* pResultado, char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	float bufferInt;
	int i;
	char bufferCadenaAux[32];
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && intentos >= 0)
	{
		for(i=0; i<=intentos; i++)
		{
			printf("\n%s\n", mensaje);
			__fpurge(stdin);
			if(myGets(bufferCadenaAux,sizeof(bufferCadenaAux))==0)
			{
				if(esNumericaFloat(bufferCadenaAux)==0)
					{
					bufferInt = atof(bufferCadenaAux);
					*pResultado = bufferInt;
					retorno = 0;
					break;
					}
				else
					{
					printf("%s", mensajeError);
					}
			}
			else
				{
				printf("%s", mensajeError);
				}
		}
		if(retorno==-1)
		{
			printf("\nTe quedaste sin intentos\n");
		}
	}
	return retorno;
}
//=========================================================================================
/**
* \brief Verifica si la cadena ingresada es numerica float
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 0 (vardadero) si la cadena es numerica y -1 (falso) si no lo es
*/
static int esNumericaFloat(char* cadena)
{
	int i=0;
	int retorno = -1;
	if(cadena != NULL && strlen(cadena) > 0)
	{
		retorno=0;
		while(cadena[i] != '\0')
			{
				if(cadena[i] < 48 || cadena[i] > 57)
					{
					if(cadena[i]==46 || cadena[i]==45)
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
//==========================================================================================
/**
 * \brief Solicita un numero int al usuario, leuego de verificarlo devuelve el resultado
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje de Error a ser mostrado
 * \param minimo Es el numero maximo a ser aceptado
 * \param maximo Es el minimo minimo a ser aceptado
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int pedirInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos)
{
	int retorno = -1;
	int bufferInt;
	int i;
	char bufferCadenaAux[32];

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && intentos >= 0)
	{
		for(i=0; i<=intentos; i++)
		{
			printf("\n%s\n", mensaje);
			__fpurge(stdin);
			if(myGets(bufferCadenaAux,sizeof(bufferCadenaAux))==0)
			{
				if(esNumericaInt(bufferCadenaAux)==0)
					{
					bufferInt = atoi(bufferCadenaAux);
					if(bufferInt >= minimo && bufferInt <= maximo)
						{
							*pResultado = bufferInt;
							retorno = 0;
							break;
						}else
							{
							printf("%s", mensajeError);
							}
					}
				else
					{
					printf("%s", mensajeError);
					}
			}
			else
				{
				printf("%s", mensajeError);
				}
		}
		if(retorno==-1)
		{
			printf("\nTe quedaste sin intentos\n");
		}
	}
	return retorno;
}
//=========================================================================================
/**
 * \brief Verifica si la cadena ingresada es numerica int
 * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 si es numerica si se obtiene un numero  y -1 si no
*/
static int esNumericaInt(char* cadena)
{
	int i=0;
	int retorno=-1;
	if(cadena!=NULL && strlen(cadena)> 0)
	{
		retorno=0;
		while(cadena[i]!='\0')
			{
				if(cadena[i]<48||cadena[i]>57)
					{
					if(cadena[i]==45)
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
//=========================================================================================
/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un máximo de 'longitud - 1' caracteres.
 * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \param len Define el tamaño de cadena
 * \return Retorna 0 si se obtiene una cadena y -1 si no
*/
static int myGets(char* pResultado, int len)
{
	int retorno=-1;
	int indexFinal;
	__fpurge(stdin);
	if(fgets(pResultado,len,stdin)!=NULL)
	{
		indexFinal = strlen(pResultado)-1;
		if(pResultado[indexFinal] == '\n')
			{
			pResultado[indexFinal] = '\0';
			}
		retorno = 0;
	}
	return retorno;
}
//=============================================================================================
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
//==============================================================================================
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
//===============================================================================================
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
//===============================================================================================
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
	return estado;
}
//==============================================================================================
/**
* \brief Calcula el factorial de numero naturales igual o mayor a 0
* \param recibe natural valor del factorial por puntero
* \return return Retorna 0 (salio bien) y -1 (salio mal)
*/
int factorial(int* result, int valor)
{
	int estado=-1;
	if (valor >= 0)
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
//===============================================================================================
