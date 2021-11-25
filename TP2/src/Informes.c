/*
 ============================================================================
 Name        : TP2.c
 Author      : Tejeda Roberto
 Version     :
 Copyright   : Your copyright notice
 Description : Employees
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

#include "ArrayEmployees.h"
#include "Pedir.h"
#include "Menu.h"
#include "Informes.h"

#define NOMINA_EMP 1000
#define OCUPADO 0
#define LIBRE -1
#define MINIMO 1
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 1000
#define SALMAX 500000

/**
* \brief pide las lista la ordena y las imprime
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna lugar el primer lugar libre de la lista o -1 si no encuentra ninguno libre
*/
int pedirLista(eEmployee *Employee, int len)
{
	int retorno=-1;
	int order;

	if(Employee!=NULL && len>0)
		{
			pedirInt(&order, "Ingrese el Orden del listado (1-ASCENDENTE Ó 2-DESCENEDENTE)","Ingrese 1 ó 2", MINIMO, 2, INTENTOS);
				if(sortEmployees(Employee, NOMINA_EMP,order)==0)
					{
						printEmployees(Employee, NOMINA_EMP);
						retorno=0;
					}else
 					puts("La lista no ha podido ser ordenada, intentelo nuevamente");
				}
	return retorno;
}
/**
* \brief pide las operaciones sobre salarios y las imprime
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna lugar el primer lugar libre de la lista o -1 si no encuentra ninguno libre
*/
int operarSalarios_2(eEmployee *Employee, int len)
{
	int retorno=-1;
	if(Employee!=NULL && len>0)
		{
		operateSalaryEmployees(Employee,NOMINA_EMP);
		retorno=0;
		}
return retorno;
}
