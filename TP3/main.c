/*
 ============================================================================
 Name        : TP3
 Author      : TEJEDA Roberto Daniel
 Version     : V 1.1
 Description : Laboratorio I / 2ªCautrimetre 2021
 ============================================================================
 */
/****************************************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

int main()
{
	int option = 0;

    LinkedList* listaEmpleados = ll_newLinkedList();

    do{
    	printf("Ingese opción\n");
    	scanf("%d",&option);

    	switch(option)
        {
            case 1:
                controller_loadFromText("data.csv",listaEmpleados);
                break;
        }
    }while(option != 10);

    puts("¡¡¡QUE HAY DE NUEVO VIEJO!!!");

    return 0;
}
