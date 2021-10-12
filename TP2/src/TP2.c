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

#define NOMINA_EMP 1000
#define OCUPADO 0
#define LIBRE -1
#define MINIMO 1
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 100000
#define SALMAX 500000

int main(void)
{
	eEmployee employees[NOMINA_EMP];
	int retornoInit;
	int menuInicial;
	int menuInformes;
	int order;
	float sumSalary;
	float promSalary;
	int overProm;
	int flagListaInit;

	retornoInit=initEmployees(employees, NOMINA_EMP);
	if (retornoInit==0)
	{
		do
		{
			imprimirMenuInicial();
			flagListaInit=listlong(employees, NOMINA_EMP);
			pedirInt(&menuInicial, "Ingese la opcion deseada", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS);
			switch (menuInicial)
			{
				case 1:
					if(loadAddEmployee(employees, NOMINA_EMP)==0)
					{
						printEmployees(employees, NOMINA_EMP);
					}else
						puts("La carga no fue posible, intentelo nuevamente");
					break;
				case 2:
					if(flagListaInit>0)
					{
						modifyOneEmploye(employees, NOMINA_EMP);
					}else
						puts(" ¡CUIDADO! No hay cargado ningun empleado");
					break;
				case 3:
					if(flagListaInit>0)
					{
						loadRemoveEmployee(employees, NOMINA_EMP);
					}else
						puts(" ¡CUIDADO! No hay ha cargado ningun empleado");
					break;
				case 4:
					if(flagListaInit>0)
					{
						do
						{
						imprimirMenuInformes();
						pedirInt(&menuInformes, "Ingese la opcion deseada", "Opciones 1, 2 ó 3", MINIMO, 3, INTENTOS);
						switch (menuInformes)
							{
							case 1:
								pedirInt(&order, "Ingrese el Orden del listado (1-ASCENDENTE Ó 2-DESCENEDENTE)","Ingrese 1 ó 2", MINIMO, 2, INTENTOS);
								if(sortEmployees(employees, NOMINA_EMP,order)==0)
								{
									printEmployees(employees, NOMINA_EMP);
								}else
								puts("La lista no ha podido ser ordenada, intentelo nuevamente");
								break;
							case 2:
								if(operateSalaryEmployees(employees, NOMINA_EMP, &sumSalary, &promSalary, &overProm)==0)
								{
									printf("\n\nLa Suma de los salarios es %.2f\n\nEl Promedio de salarios %.2f\n\n"
											"La cantidad de salarios que superan el promedio es %d\n\n",sumSalary,promSalary,overProm);
								}else
								puts("No se han podido calcular los datos");
								break;
							default:
								break;
							}
						}while(menuInformes<3);
					}else
						puts(" ¡CUIDADO! No hay cargado ningun empleado");
					break;
				case 5:
					pedirInt(&menuInicial, "CONFIRME QUE DESEA ABANDONAR LA NOMINA INGRESANDO 5 sino ingrese 1", "Opciones entre 1 y 5",MINIMO, MAXIMO, INTENTOS);
					break;
				default:
					break;
			}
		}while(menuInicial<5);
	}else
		puts("La nomina de Empleados no se ha podido inicializar");
	puts("La ejecución de la nomina a finalizado");
	return EXIT_SUCCESS;
}
