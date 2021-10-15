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
#include "Informes.h"

/**
* \brief Imprime el menu principal
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
