#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "ValidarPedir.h"
/**
* \brief pide un texto al ususario
* \param *pResultado, len tamaño del array, *mensaje, *mensajeError, intentos
* \return Retorna -1  salio mal, 0 salio bien
*/
int pedirNombre(char *pResultado, int len, char *mensaje, char *mensajeError, int intentos)
{
	int retorno = -1;
	int i;
	char bufferCadenaAux[128];
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && intentos >= 0)
	{
		for(i=0; i<=intentos; i++)
		{
			printf("\n%s\n", mensaje);
			__fpurge(stdin);
			if(myGets(bufferCadenaAux,sizeof(bufferCadenaAux))==0  && strlen(bufferCadenaAux)>0)
			{
				strncpy(pResultado, bufferCadenaAux,len);
				if (esNombre(pResultado)==0)
				{
					retorno = 0;
				break;
				}
			}else
				{
					printf("%s", mensajeError);
				}
		}
	}else
		 puts("No se ha podido procesar");
	return retorno;
}
/**
  * \brief Solicita un numero al usuario, leuego de verificarlo devuelve el resultado
  * \param *pResultado, *mensaje, *mensajeError, minimo, maximo, intentos
  * \return Retorna 0 si se obtuvo el numero y -1 si no
  */
 int pedirInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int intentos)
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
 	}else
		 puts("No se ha podido procesar");
 	return retorno;
 }
/**
  * \brief Verifica si la cadena ingresada es numerica
  * \param *cadena Puntero al espacio de memoria donde se dejara el resultado de la funcion
  * \return Retorna 0 si se obtiene un numero  y -1 si no
 */
 int esNumericaInt(char *cadena)
 {
 	int i=0;
 	int retorno=-1;
 	if(cadena!=NULL && strlen(cadena)> 0)
 	{
 		retorno=0;
 		while(cadena[i]!='\0')
 			{
 				if(cadena[i]<'0'||cadena[i]> '9')
 					{
 					retorno=-1;
 					break;
 					}
 				i++;
 			}
 	}else
		 puts("No se ha podido procesar");
 	return retorno;
 }
 /**
  * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena un máximo de 'longitud - 1' caracteres.
  * \param *pResultado paso por referncia el array, len tamaño del array
  * \return Retorna 0 si se obtiene una cadena y -1  si no
 */
 int myGets(char *pResultado, int len)
 {
 	int retorno=-1;
 	int indexFinal;
 	if(fgets(pResultado,len,stdin)!=NULL)
 	{
 		__fpurge(stdin);
 		indexFinal = strlen(pResultado)-1;
 		if(pResultado[indexFinal] == '\n')
 			{
 			pResultado[indexFinal] = '\0';
 			}
 		retorno = 0;
 	}else
		 puts("No se ha podido procesar");
 	return retorno;
 }
/**
* \brief Verifica si la cadena ingresada es alfabetica
* \param *cadena Paso por referencia Cadena de caracteres a ser analizada
* \return Retorna 0 si la cadena es alfa numerica y -1 si no lo es
*/
int esNombre(char *cadena)
{
	int i=0;
	int retorno = 0;
	if(cadena != NULL)
	{
		while(cadena[i]!='\0')
			{
				if((cadena[i]<'A'||cadena[i]>'Z')&&(cadena[i]<'a'||cadena[i]>'z'))
					{
						if (cadena[i]==' ')
						{
							if(i==0)
							{
								retorno=-1;
								break;
							}
						}else if(cadena[i]=='-')
							{
								break;
							}else
								{
									retorno = -1;
									break;
								}
					}
				if(i==0 && (cadena[i]<'A'||cadena[i]>'Z'))
					{
						puts("El nombre debe empezar con mayuscula");
						retorno=-1;
						break;
					}
				i++;
			}
	}else
		 puts("No se ha podido procesar");
	return retorno;
}
