/*
 * utn.c
 *
 *  Created on: 20 sep. 2021
 *      Author: usuario
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utn.h"

#define INTENTOS 5

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

/*
 * 1.
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
 */




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

/**
* \brief: Pide un float, con cantidad de intentos y mensajes al usuario
* \param; cantidad de intento, mensajes pedir y erro, puntero float de valor
* \return Retorna 1 salio mal, 0 salio bien y 2 sin reintento
*/
int pedirNumeroFloat(float* px, int intentos, char* txt, char* txtError)
{
	float buffer;
	int retorno=-1; //No se pudieron validar parametros
	int i;
	int salidaScanf;
	if(px != NULL && intentos >=0 && txt != NULL && txtError != NULL)
	{
		for (i=0; i<=intentos; i++)
		{
			printf("%s",txt);
			__fpurge(stdin);
			salidaScanf=scanf("%f", &buffer);
			if (salidaScanf>0)
			{
				retorno = 0; // OK cargo float
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
