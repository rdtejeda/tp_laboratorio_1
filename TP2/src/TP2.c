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

int main(void)
{
	eEmployee employees[NOMINA_EMP];
	int retornoInit;
	int menuInicial;
	int menuInformes;
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
								pedirLista(employees, NOMINA_EMP);
								break;
							case 2:
								operarSalarios_2(employees, NOMINA_EMP);
								break;
							default:
								break;
							}
						}while(menuInformes<3);
					}else
						puts("¡CUIDADO! No hay cargado ningún empleado");
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
