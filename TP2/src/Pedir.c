/*
 *  Pedir.c
 *  Created on: 7 oct. 2021
 *  Author: Tejeda Roberto
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

#include "ArrayEmployees.h"
#include "Pedir.h"

#define NOMINA_EMP 1000
#define OCUPADO 0
#define LIBRE -1
#define MINIMO 1
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 100000
#define SALMAX 500000

static int dameUnIdNuevo();


//============================================================
/**
* \brief Pide al ususario todos los datos de el nuevo empleado a ser cargado y llama a la funcio para dar de alta
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return retona -1 si no pudo ser cargado el array o 0 si salio todo bien.
*/
int loadAddEmployee(eEmployee *plistEmployee, int len)
{
	int retorno=-1;
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int retornoAddEmplyee;
	if(findFreePlace(plistEmployee, NOMINA_EMP)>=0 && len>0)
		{
		puts("Estamos por dar de alta un nuevo empleado, por favor ingrese los datos solicitados");
			do
				{
					id=dameUnIdNuevo();
					if(id>0)
					{
						if(pedirText(name, sizeof(name), "Ingrese Nombre", "Ingrese Nombre valido", INTENTOS)==0)
						{
							if (pedirText(lastName, sizeof(lastName), "Ingrese Apellido", "Ingrese Apellido valido", INTENTOS)==0)
							{
								if(pedirFloat(&salary, "Ingrese salario", "Ingrese monto valido", SALMIN, SALMAX, INTENTOS)==0)
								{
									if(pedirInt(&sector, "Ingrese sector", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS)==0)
									{
										retornoAddEmplyee=addEmployee(plistEmployee, NOMINA_EMP, id, name, lastName, salary, sector);
									}
								}
							}
						}
					}
				}while(retornoAddEmplyee!=0);
		}else
			{
				puts("NO HAY LUGAR DISPONIBLE");
			}
	retorno=0;
	return retorno;
}
//============================================================================================================
/**
* \brief Pide al ususario todos los datos de el empleado a remover y llama a la funcio para eliminarlo
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return retona -1 si no pudo ser cargado el array o 0 si salio todo bien.
*/

int loadRemoveEmployee(eEmployee *plistEmployee, int len)
{
	int retorno=-1;
	int idBaja;
	printEmployees(plistEmployee, NOMINA_EMP);
	pedirInt(&idBaja, "Ingrese el Id a dar de baja", "Ingrese ID valido", MINIMO, NOMINA_EMP, INTENTOS);
	removeEmployee(plistEmployee, NOMINA_EMP,idBaja);
	printEmployees(plistEmployee, NOMINA_EMP);

	return retorno;
}
//==========================================================
/**
* \brief Imprime el menu de INICIAL de opciones
* \param
* \return
*/
void imprimirMenuInicial()
{
	puts("MENU PRINCIPAL");
	puts("1- ALTAS");
	puts("2- MODIFICAR");
	puts("3- BAJA");
	puts("4- INFORMAR");
	puts("5- SALIR DE NOMINA");
}
//===========================================================
/**
* \brief Imprime el menu de informes
* \param
* \return
*/
void imprimirMenuInformes()
{
	puts("1- Listado de los empleados ordenados alfabéticamente por Apellido y Sector");
	puts("2- Total y promedio de los salarios, y cuántos empleados superan el salario promedio");
	puts("3- SALIR DE INFORMES");
}
//===========================================================
/**
* \brief Imprime el menu de opciones para modoficar datos del usuario
* \param
* \return
*/
void imprimirMenuModificar()
{
	puts("1- Modificar Nombre");
	puts("2- Modificar Apellido");
	puts("3- Modificar Salario");
	puts("4- Modificar Sector");
	puts("5- SALIR DE CAMBIOS");
}
//===========================================================
/**
* \brief pide un texto al ususario
* \param *pResultado, len tamaño del array, *mensaje, *mensajeError, intentos
* \return Retorna -1  salio mal, 0 salio bien
*/
int pedirText(char *pResultado, int len, char *mensaje, char *mensajeError, int intentos)
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
				if (esAlfaumerica(pResultado)==0)
				{
					retorno = 0;
				break;
				}
			}else
				{
					printf("%s", mensajeError);
				}
		}
	}
	return retorno;
}
 //==================================================================================================
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
 	}
 	return retorno;
 }
 //=====================================================================================================
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
 	}
 	return retorno;
 }
 //=====================================================================================================
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
 	}
 	return retorno;
 }
 //==================================================================================================
 /**
  * \brief Solicita un numero al usuario, leuego de verificarlo devuelve el resultado
  * \param *pResultado, *mensaje, *mensajeError, minimo, maximo, intentos
  * \return Retorna 0 si se obtuvo el numero y -1 si no
  */
 int pedirFloat(float *pResultado, char *mensaje, char *mensajeError, float minimo, float maximo, int intentos)
 {
 	int retorno = -1;
 	float bufferInt;
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
 				if(esNumericaFloat(bufferCadenaAux)==0)
 					{
 					bufferInt = atof(bufferCadenaAux);
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
 //=========================================================================================================
 /**
 * \brief Verifica si la cadena ingresada es numerica
 * \param *cadena paso por referencia Cadena de caracteres a ser analizada
 * \return Retorna 0  si la cadena es numerica y -1  si no lo es
 */
 int esNumericaFloat(char *cadena)
 {
 	int i=0;
 	int retorno = -1;
 	int contNeg=0;
 	int contPuntos=0;
 	if(cadena != NULL && strlen(cadena) > 0)
 	{
 		retorno=0;
 		while(cadena[i] != '\0')
 			{
 				if(cadena[i] < '0' || cadena[i] > '9')
 					{
 					if(cadena[i]=='-' || cadena[i]=='.')
 						{
 							if(cadena[i]=='-')
 							{
 								contNeg++;
 								if(i!=0)
 								{
 									retorno = -1;
 									break;
 								}
 							}
 							if(cadena[i]=='.')
 							{
 								contPuntos++;
 							}
 						}else
 						{
 							retorno = -1;
 							break;
 						}
 					}
 				i++;
 			}
 		if(contNeg>1 ||contPuntos>1)
 		{
 			retorno=-1;
 		}
 	}
 	return retorno;
 }
//===================================================================================================
/**
* \brief Verifica si la cadena ingresada es alfanumerica
* \param *cadena Paso por referencia Cadena de caracteres a ser analizada
* \return Retorna 0 si la cadena es alfa numerica y -1 si no lo es
*/
int esAlfaumerica(char *cadena)
{
	int i=0;
	int retorno = 0;
	if(cadena != NULL && strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
			{
				if((cadena[i]<'0'||cadena[i]>'9')&&(cadena[i]<'A'||cadena[i]>'Z')&&(cadena[i]<'a'||cadena[i]>'z')&&cadena[i]==164&&cadena[i]==165)
					{
						if (cadena[i]==' ')
						{
							if(i==0)
							{
								retorno=-1;
								break;
							}
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
//===================================================================================
/**
  * \brief me devuelve un id consecutivo y no repetido, mientras se ejecute el programa, memorizando el ultimo valor
  * \param void
  * \return Retorna numero de id
  */
static int dameUnIdNuevo()
{
	static int contador=0;
	contador++;
	return contador;
}
//==============================================================================
