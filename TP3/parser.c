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

/*
 *brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *param *PFile al archivo, *pArray a la LInkedList
 *return 0 si lo logro la carga y -1 si salio mal
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
int retorno=-1;
Employee* pAuxiliarEmployee;
char id[16];
char nombre[128];
char horasTrabajadas[16];
char sueldo[32];
if(pFile!=NULL && pArrayListEmployee!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo); // salteo la 1era
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo)==4)
				{
				pAuxiliarEmployee = employee_newParametros(id,nombre,horasTrabajadas,sueldo);
				if(pAuxiliarEmployee!=NULL)
						ll_add(pArrayListEmployee,pAuxiliarEmployee);
				}else
					break;
		}while(feof(pFile)==0 );
		retorno=0;
	}else
		puts("No se ha podido cargar la informacion desde *.csv");
return retorno;
}

/*
 * brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 * param *pFile al Archivo , pArrayListEmployee LinkedList*
 * \return  0 si lo logro la carga y -1 si salio mal *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
int retorno=-1;
Employee* pAuxiliarEmployee;
if(pFile!=NULL&&pArrayListEmployee!=NULL)
	{
		do
		{
			if((pAuxiliarEmployee=employee_new())!=NULL && fread(pAuxiliarEmployee,sizeof(Employee),1,pFile)==1)
				{
				ll_add(pArrayListEmployee, pAuxiliarEmployee);
				}else
					employee_delete(pAuxiliarEmployee);
		}while(feof(pFile)==0);
	}
return retorno;
}
