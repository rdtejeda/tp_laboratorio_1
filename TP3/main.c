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
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "ValidarPedir.h"
#include "Menu.h"

int main()
{
	int option=0;
	int loadCsv=-1;
	int loadBin=-1;
	//int saveCsv=-1;
	//int saveBin=-1;
    LinkedList* listaEmpleados = ll_newLinkedList();
    do{
    	option=menuPrincipal();
    	switch(option)
        {
            case 1:
            	if(loadBin==-1&&loadCsv==-1)
					loadCsv=controller_loadFromText("Midata.csv",listaEmpleados);
					else
						puts("La lista ya ha sido cargado");
                break;
            case 2:
            	if(loadBin==-1&&loadCsv==-1)
					loadBin=controller_loadFromBinary("Midata.bin",listaEmpleados);
					else
						puts("La lista ya ha sido cargado");
            	break;
            case 3:
            	if(loadBin==0||loadCsv==0)
					controller_addEmployee(listaEmpleados);
					else
						puts("Antes de Cargar un nuevo empleado debe cargar la lista");
                break;
            case 4:
            	if(loadBin==0||loadCsv==0)
            		controller_editEmployee(listaEmpleados);
            		else
            			puts("Antes de Modificar un empleado debe cargar la lista");
                break;
            case 5:
            	if(loadBin==0||loadCsv==0)
            		controller_removeEmployee(listaEmpleados);
            		else
            		    puts("Antes de Remover un empleado debe cargar la lista");
                break;
            case 6:
            	if(loadBin==0||loadCsv==0)
            		controller_ListEmployee(listaEmpleados);
            		else
            		   puts("Antes de Listar los Empleado debe cargar la lista");
                break;
            case 7:
            	if(loadBin==0||loadCsv==0)
            		controller_sortEmployee(listaEmpleados);
            		else
            			puts("Antes de Ordenar la Lista de empleados debe cargarla");
                break;
            case 8:
            	if(loadBin==0||loadCsv==0)
					controller_saveAsText("Midata.csv",listaEmpleados);//saveCsv=
					else
						puts("Se debe cargar la lista antes de poder grabar");
                break;
            case 9:
            	if(loadBin==0||loadCsv==0)
					controller_saveAsBinary("Midata.bin",listaEmpleados);//saveBin=
					else
						puts("Se debe cargar la lista antes de poder grabar");
                break;
        }
    }while(option != 10);
    controller_shotdown(listaEmpleados,loadBin,loadCsv);
    puts("¡¡¡QUE HAY DE NUEVO VIEJO!!!");
 return 0;
}
