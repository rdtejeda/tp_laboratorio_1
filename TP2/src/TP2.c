/*
 ============================================================================
 Name        : TP2.c
 Author      : Tejeda Roberto
 Version     :
 Copyright   : Your copyright notice
 Description : Employee
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

#include "ArrayEmployees.h"
#include "Pedir.h"

#define NOMINA_EMP 10
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
	int id;
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
			pedirInt(&menuInicial, "Ingese la opcion deseada", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS);
			switch (menuInicial)
			{
				case 1:
					flagListaInit=loadNewEmployee(employees, NOMINA_EMP);
					break;
				case 2:
					if(flagListaInit==0)
					{
					modifyOneEmploye(employees, NOMINA_EMP);
					}else
						puts(" ¡CUIDADO! Aún no se ha cargado ningun empleado");
					break;
				case 3:
					if(flagListaInit==0)
					{
					printEmployees(employees, NOMINA_EMP);
					pedirInt(&id, "Ingrese el Id a dar de baja", "Ingrese valor valido", MINIMO, NOMINA_EMP, INTENTOS);
					removeEmployee(employees, NOMINA_EMP,id);
					}else
						puts(" ¡CUIDADO! Aún no se ha cargado ningun empleado");
					break;
				case 4:
					if(flagListaInit==0)
					{
						do
						{
						imprimirMenuInformes();
						pedirInt(&menuInformes, "Ingese la opcion deseada", "Opciones 1, 2 y 3", MINIMO, 3, INTENTOS);
						switch (menuInformes)
							{
							case 1:
								pedirInt(&order, "Ingrese Orden del listado = Ascendente 1 - Descendente 2","Ingrese 1 o 2", MINIMO, 2, INTENTOS);
								sortEmployees(employees, NOMINA_EMP,order);
								printEmployees(employees, NOMINA_EMP);
								break;
							case 2:
								operateSalaryEmployees(employees, NOMINA_EMP, &sumSalary, &promSalary, &overProm);
								printf("\nLa Suma de los salarios es %.2f\nEl Promedio de salarios %.2f\nLa cantidad de salarios que superan el promedio es %d\n",sumSalary,promSalary,overProm);
								break;
							}
						}while(menuInformes<3);
					}else
						puts(" ¡CUIDADO! Aún no se ha cargado ningun empleado");
			}
		}while(menuInicial<5);
	}else
		{
			puts("La nomina de Empleados no se ha podido inicializar");
		}

	puts("!!!Que hay de nuevo viejo!!!");

	return EXIT_SUCCESS;
}
