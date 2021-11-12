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
#include "Menu.h"

#define MINIMO 1
#define MAXIMO 10
#define INTENTOS 3
#define MAXIMO4 4

/**
  * \brief imprime el menu principal, pide la opcion deseada
  * \param void
  * \return Retorna opcion deseada si todo bien  y -1 si no lo logra
  */
int menuPrincipal()
{
	int opcion=-1;
	puts("****************************************************************************");
	puts("Menu Principal:");
	puts("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).");
	puts("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).");
	puts("3. Alta de empleado.");
	puts("4. Modificar datos de empleado.");
	puts("5. Baja de empleado.");
	puts("6. Listar empleados.");
	puts("7. Ordenar empleados.");
	puts("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).");
	puts("9. Guardar los datos de los empleados en el archivo data.bin (modo binario).");
	puts("10. Salir");
	puts("******************************************************************************");
	pedirInt(&opcion,"Ingese la opción deseada","ERROR-Ingrese un numero entre 1y10",MINIMO,MAXIMO,INTENTOS);
return opcion;
}
/**
  * \brief imprime el menu de selecion, pide la opcion deseada
  * \param void
  * \return Retorna opcion deseada si todo bien  y -1 si no lo logra
  */
int menuSeleccion()
{
	int opcion=-1;
puts("****************************************************************************");
puts("Buscar Empleado Por:");
puts("1. Id");
puts("2. Nombre");
puts("3. Salir");
puts("******************************************************************************");
pedirInt(&opcion,"Par buscar por Id ingrese 1 y para buscar por nombre 2","Error-Imgrese entre 1 y 3",MINIMO,INTENTOS,INTENTOS);
return opcion;
}
/**
  * \brief imprime el menu de edicion, pide la opcion deseada
  * \param void
  * \return Retorna opcion deseada si todo bien  y -1 si no lo logra
  */
int menuOpcion()
{
	int opcion=-1;
puts("****************************************************************************");
puts("Elija Opcion:");
puts("1. Nombre");
puts("2. Horas Trabajadas");
puts("3. Sueldo");
puts("4. Salir");
puts("******************************************************************************");
pedirInt(&opcion,"Seleccione dato a modificar","Error-Imgrese entre 1 y 4",MINIMO,MAXIMO4,INTENTOS);
return opcion;
}
/**
  * \brief imprime el menu de criterio de ordenamiento
  * \param void
  * \return Retorna opcion deseada si todo bien  y -1 si no lo logra
  */
int menuCriterio()
{
	int opcion=-1;
puts("****************************************************************************");
puts("Elija Opcion:");
puts("1. Nombre");
puts("2. Horas Trabajadas");
puts("3. Sueldo");
puts("4. ID");
puts("******************************************************************************");
pedirInt(&opcion,"Seleccione dato a modificar","Error-Imgrese entre 1 y 4",MINIMO,MAXIMO4,INTENTOS);
return opcion;
}
void imprimirEncabezado()
{
	puts("----------------------------------------------------------------------------");
	printf("ID\tNombre de el Empleado\tHoras  Sueldo\n");
	puts("----------------------------------------------------------------------------");
}
