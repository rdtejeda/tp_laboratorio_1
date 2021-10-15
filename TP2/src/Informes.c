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
#define SALMIN 50000
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
	float sumSalary;
	float promSalary;
	int overProm;

	if(operateSalaryEmployees(Employee, NOMINA_EMP, &sumSalary, &promSalary, &overProm)==0 && Employee!=NULL && len>0)
		{
			printf("\n\nLa Suma de los salarios es %.2f\n\nEl Promedio de salarios %.2f\n\n"
					"La cantidad de salarios que superan el promedio es %d\n\n",sumSalary,promSalary,overProm);
			retorno=0;
		}else
			puts("No se han podido calcular los datos");
	return retorno;
}
