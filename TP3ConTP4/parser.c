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
 *brief Parsea los datos los datos de los empleados desde el archivo *.csv (modo texto).
 *param *PFile al archivo, *pArray a la LInkedList
 *return 0 si lo logro la carga y -1 si salio mal
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pLinkedListEmpleados)
{
int retorno=-1;
int paso=0;
Employee* pAuxiliarEmployee;
char id[16];
char nombre[128];
char horasTrabajadas[16];
char sueldo[32];
if(pFile!=NULL && pLinkedListEmpleados!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo); // salteo la 1era
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo)==4)
				{
				pAuxiliarEmployee = employee_newParametros(id,nombre,horasTrabajadas,sueldo);
				if(pAuxiliarEmployee!=NULL)
						ll_add(pLinkedListEmpleados,pAuxiliarEmployee);
				}else
					break;
		paso++;
		}while(feof(pFile)==0 );
		retorno=0;
		printf("Se han agregado a la lista %d empleados\n",paso);
	}else
		puts("No se ha podido cargar la informacion desde *.csv");
return retorno;
}
/*
 * brief Parsea los datos los datos de los empleados desde el archivo *.bin (modo binario).
 * param *pFile al Archivo , pLinkedListEmpleados LinkedList*
 * \return  0 si lo logro la carga y -1 si salio mal *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pLinkedListEmpleados)
{
int retorno=-1;
Employee* pAuxiliarEmployee;
if(pFile!=NULL&&pLinkedListEmpleados!=NULL)
	{
		do
		{
			if((pAuxiliarEmployee=employee_new())!=NULL && fread(pAuxiliarEmployee,sizeof(Employee),1,pFile)==1)
				{
				ll_add(pLinkedListEmpleados, pAuxiliarEmployee);
				}else
					employee_delete(pAuxiliarEmployee);
		}while(feof(pFile)==0);
	}
return retorno;
}
//=============================================================================================================
/*
 *brief Parsea y cuenta la cantidad de empleados desde el archivo *.csv (modo texto).
 *param *PFile al archivo
 *return cantidad de empleados si lo logro la carga y -1 si salio mal
 */
int parser_countEmployeeFromText(FILE* pFile)
{
int retorno=-1;
int paso=0;
char id[16];
char nombre[128];
char horasTrabajadas[16];
char sueldo[32];
if(pFile!=NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo); // salteo la 1era
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id,nombre,horasTrabajadas,sueldo)==4)
				{
				paso++;
				}else
					break;
		}while(feof(pFile)==0 );
		retorno=paso;
		printf("El archivo csv contiene %d empleados\n",retorno);
	}else
		puts("No se ha podido cargar la informacion desde *.csv");
return retorno;
}

/*
 * brief Parsea y cuenta la cantidad de empleados desde el archivo *.bin (modo texto).
 * param *pFile al Archivo
 * \return cantidad de empleados 0 si lo logro la carga y -1 si salio mal *
 */
int parser_countEmployeeFromBinary(FILE* pFile)
{
int retorno=-1;
int paso=0;
Employee* pAuxiliarEmployee;
if(pFile!=NULL)
	{
		do
		{
			if((pAuxiliarEmployee=employee_new())!=NULL && fread(pAuxiliarEmployee,sizeof(Employee),1,pFile)==1)
				{
				paso++;
				employee_delete(pAuxiliarEmployee);
				}else
					employee_delete(pAuxiliarEmployee);
		}while(feof(pFile)==0);
		retorno=paso;
		printf("El archivo csv contiene %d empleados\n",retorno);
	}
return retorno;
}
//==================================================================================================================
