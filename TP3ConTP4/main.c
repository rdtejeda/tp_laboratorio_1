/*
 ============================================================================
 Name        : TP3
 Author      : TEJEDA Roberto Daniel
 Version     : V 1.1
 Description : Laboratorio I / 2ªCautrimetre 2021
 ============================================================================
*/
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
	LinkedList* pLinkedListEmpleados=ll_newLinkedList();
	puts("¡BIENVENIDO A LA APLICACION 'NOMINA DE EMPLEADOS'!");
        do{
    	option=menuPrincipal();
    	switch(option)
        {
            case 1:
            	if(loadBin==-1&&loadCsv==-1)
            		{
						loadCsv=controller_loadFromText("data.csv",pLinkedListEmpleados);
					}else
						puts("La carga desde archivo ya ha sido realizada");
                break;
            case 2:
            	if(loadBin==-1&&loadCsv==-1)
					{
						loadCsv=controller_loadFromBinary("data.bin",pLinkedListEmpleados);
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
						controller_saveAsText("data.csv",pLinkedListEmpleados);//saveCsv=
					}else
						puts("Debe cargar la lista desde un archivo antes de poder grabar");
                break;
            case 9:
            	if(loadBin==0||loadCsv==0)
					{
						controller_saveAsBinary("data.bin",pLinkedListEmpleados);
					}else
						puts("Debe cargar la lista desde un archivo antes de poder grabar");
                break;
            default:
             	 break;
        }
    }while(option != 10);
    controller_shotdown(pLinkedListEmpleados,loadBin,loadCsv);
    puts("¡SALIO DE LA APLICACION 'NOMINA DE EMPLEADOS'!");
 return 0;
}
