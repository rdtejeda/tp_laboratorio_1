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
	LinkedList* pLinkedListEmpleados = ll_newLinkedList();
        do{
    	option=menuPrincipal();
    	switch(option)
        {
            case 1:
            	if(loadBin==-1&&loadCsv==-1)
            		{
						loadCsv=controller_loadFromText("Midata.csv",pLinkedListEmpleados);
					}else
						puts("La carga desde archivo ya ha sido realizada");
                break;
            case 2:
            	if(loadBin==-1&&loadCsv==-1)
					{
						loadCsv=controller_loadFromBinary("Midata.bin",pLinkedListEmpleados);
					}else
            			puts("La carga desde archivo ya ha sido realizada");
            	break;
            case 3:
            		controller_addEmployee(pLinkedListEmpleados);
				break;
            case 4:
            		controller_editEmployee(pLinkedListEmpleados);
            	break;
            case 5:
            		controller_removeEmployee(pLinkedListEmpleados);
            	break;
            case 6:
               		controller_ListEmployee(pLinkedListEmpleados);
            	break;
            case 7:
               		controller_sortEmployee(pLinkedListEmpleados);
                break;
            case 8:
            	if(loadBin==0||loadCsv==0)
					{
						controller_saveAsText("Midata.csv",pLinkedListEmpleados);//saveCsv=
					}else
						puts("Debe cargar la lista desde un archivo antes de grabar");
                break;
            case 9:
            	if(loadBin==0||loadCsv==0)
					{
						controller_saveAsBinary("Midata.bin",pLinkedListEmpleados);
					}else
						puts("Debe cargar la lista desde un archivo antes de grabar");
                break;
            default:
             	 break;
        }
    }while(option != 10);
    controller_shotdown(pLinkedListEmpleados,loadBin,loadCsv);
    puts("¡¡¡QUE HAY DE NUEVO VIEJO!!!");
 return 0;
}
