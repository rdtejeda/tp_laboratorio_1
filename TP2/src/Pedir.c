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

#define NOMINA_EMP 10
#define OCUPADO 0 //isEmpty flag OCUPADA O LLENA
#define LIBRE -1  //isEmpty flag
#define MINIMO 0
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 100000
#define SALMAX 500000


int loadNewEmployee(eEmployee plistEmployee[], int len)
{
	int retorno=-1;
	int id;
	char name[51];
	char lastName[51];
	float salary;
	int sector;
	int retornoAddEmplyee;
	if(buscarLugarLibre(plistEmployee, NOMINA_EMP)>=0 && len>0)
		{
			do
				{
				id=dameUnIdNuevo();
				pedirText(name, sizeof(name), "Ingrese Nombre", "Ingrese Nombre valido", INTENTOS);
				pedirText(lastName, sizeof(lastName), "Ingrese Apellido", "Ingrese Apellido valido", INTENTOS);
				pedirFloat(&salary, "Ingrese salario", "Ingrese monto valido", SALMIN, SALMAX, INTENTOS);
				pedirInt(&sector, "Ingrese sector", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS);
				retornoAddEmplyee=addEmployee(plistEmployee, NOMINA_EMP, id, name, lastName, salary, sector);
				}while(retornoAddEmplyee!=0);
		}else
			{
				puts("NO HAY LUGAR DISPONIBLE");
			}
	retorno=0;
	return retorno;
}
//==========================================================
/**
* \brief Imprime menu de opciones
* \param
* \return
*/
void imprimirMenuInicial()
{
	puts("1- ALTAS");
	puts("2- MODIFICAR");
	puts("3- BAJA");
	puts("4- INFORMAR");
	puts("5- SALIR");
}
//===========================================================
/**
* \brief Imprime menu de informe
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
* \brief Imprime menu de opciones
* \param
* \return
*/
void imprimirMenuModificar()
{
	puts("1- Modificar Nombre");
	puts("2- Modificar Apellido");
	puts("3- Modificar Salario");
	puts("4- Modificar Sector");
	puts("5- Aceptar cambios");
}
//===========================================================
/**
* \brief pide un texto al ususario
* \param puntero cahr, reintentos y textos de pedido y error , intentos
* \return Retorna -1  salio mal, 0 salio bien y 2 sin reintento
*/
int pedirText(char* pResultado, int len, char* mensaje, char* mensajeError, int intentos)
{
	int retorno = -1;
	int i;
	char bufferCadenaAux[128];//esto
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && intentos >= 0)
	{
		for(i=0; i<=intentos; i++)
		{

			printf("\n%s\n", mensaje);
			__fpurge(stdin);
			if(myGets(bufferCadenaAux,sizeof(bufferCadenaAux))==0)
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
 //=====================================================================================================
 /**
  * \brief Verifica si la cadena ingresada es numerica
  * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
  * \return Retorna 0 (EXITO) si se obtiene un numero  y -1 (ERROR) si no
 */
 int esNumericaInt(char* cadena)
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
  * \param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
  * \param len Define el tamaño de cadena
  * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 */
 int myGets(char pResultado[], int len)
 {
 	int retorno=-1;
 	int indexFinal;
 	//__fpurge(stdin);
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
  * \param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
  * \param mensaje Es el mensaje a ser mostrado
  * \param mensajeError Es el mensaje de Error a ser mostrado
  * \param minimo Es el numero maximo a ser aceptado
  * \param maximo Es el minimo minimo a ser aceptado
  * \return Retorna 0 si se obtuvo el numero y -1 si no
  */
 int pedirFloat(float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos)
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
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 0 (vardadero) si la cadena es numerica y -1 (falso) si no lo es
 */
 int esNumericaFloat(char* cadena)
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
* \param cadena Cadena de caracteres a ser analizada
* \return Retorna 0 (vardadero) si la cadena es numerica y -1 (falso) si no lo es
*/
int esAlfaumerica(char* cadena)
{
	int i=0;
	int retorno = 0;
	if(cadena != NULL && strlen(cadena) > 0)
	{
		while(cadena[i] != '\0')
			{
				if((cadena[i]<48||cadena[i]>57)&&(cadena[i]< 65||cadena[i]>90)&&(cadena[i]<97||cadena[i]>122))//0-9 48-57 A-Z 65-90 a-z 97-122
					{
						if (cadena[i]==32)
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
//==============================================================================
/**
* \brief pide un char al ususario
* \param puntero cahr, reintentos y textos de pedido y erro
* \return Retorna -1  salio mal, 0 salio bien y 2 sin reintento
*/
int pedirCharAUsuario(char* pChar, int reintentos, char* txt, char* txtError)
{
	int retorno=-1;
	int i;
	char bufferCadenaAux[32];
	if(pChar != NULL && reintentos >=0 && txt != NULL && txtError != NULL)
	{
		for (i=0; i<=reintentos; i++)
		{
			printf("\n%s\n", txt);
			__fpurge(stdin);
			if(myGets(bufferCadenaAux,sizeof(bufferCadenaAux))==0)
				{
				//if(es loque necesite)
				strncpy(pChar, bufferCadenaAux,1);
					retorno = 0;
					break;
				}else
				{
						printf("%s", txtError);
				}
		}
	}
	return retorno;
}
//===================================================================================
