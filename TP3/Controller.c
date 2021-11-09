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
#include "parser.h"
#include "Menu.h"

#define MINIMO 1
#define MAXIMO 10
#define INTENTOS 3
#define MAXIMOHORAS 300
#define MAXIMOSUELDO 500000

/*
 * brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 * param *char path de archivo y *pArrayListEmployee a LinkedList
 * return 0 si lo logro la carga y -1 si salio mal
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	if(path!=NULL && pArrayListEmployee!=NULL)
		{
		FILE* pFileCsv;
		pFileCsv=fopen(path,"r");
		if(pFileCsv!=NULL)
			{
				parser_EmployeeFromText(pFileCsv,pArrayListEmployee);
				fclose(pFileCsv);
				retorno=0;
				puts("La lista se ha cargado desde el *.csv");
			}else
				puts("No se ha podido abrir el archivo");
		}else
			puts("Parametros erroneos");
return retorno;
}
/*
 * brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 * param param *char path de archivo y *pArrayListEmployee a LinkedList
 * return 0 si lo logro la carga y -1 si salio mal
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int estado=-1;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		FILE* pFileBin;
		pFileBin=fopen(path,"r");
		if(pFileBin!=NULL)
				{
				parser_EmployeeFromBinary(pFileBin, pArrayListEmployee);
				fclose(pFileBin);
				puts("La lista se ha cargado desde el *.bin");
				estado=0;
				}else
					 puts("No se ha podido abrir el archivo");
	}else
		puts("Parametros erroneos");
return estado;
}
/*
 * brief da el alta a un empleado
 * param pArrayListEmployee LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	char idStr[16];
	char nombreStr[128];
	char horasTrabajadasStr[16];
	char sueldoStr[32];
	int idBuffer;
	int horasTrabajadasBuffer;
	int sueldoBuffer;
	Employee* bufferEmployee;
	if(pArrayListEmployee!=NULL)
	{
		idBuffer=dameUnIdNuevoEmployee();
		sprintf(idStr,"%d",idBuffer);
		pedirNombre(nombreStr,sizeof(nombreStr),"Ingrese Nombre de Nuevo Empleado","ERROR-Ingrese Texto Correcto",INTENTOS);
		pedirInt(&horasTrabajadasBuffer, "Ingese Horas Trabajadas", "Ingres numero correcto", MINIMO, MAXIMOHORAS,INTENTOS);
		sprintf(horasTrabajadasStr,"%d",horasTrabajadasBuffer);
		pedirInt(&sueldoBuffer, "Ingrese Sueldo", "Ingrese monto correcto",MINIMO,MAXIMOSUELDO,INTENTOS);
		sprintf(sueldoStr,"%d",sueldoBuffer);
		bufferEmployee=employee_newParametros(idStr,nombreStr,horasTrabajadasStr,sueldoStr);
		if(bufferEmployee!=NULL)
			{
			if(!ll_add(pArrayListEmployee,bufferEmployee))
				{
				puts("Se ha dado de alta al siguiente empleado");
				controller_ListOneEmployee(pArrayListEmployee, ll_indexOf(pArrayListEmployee, bufferEmployee));
				retorno=0;
				}else
				puts("No se ha podio agrega a la lista");
			}else
				puts("No se ha podido los parametro");
	}else
		puts("La lista no esta iniciada");
return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	if(pArrayListEmployee!=NULL)
	employee_modify(pArrayListEmployee);
return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	if(pArrayListEmployee!=NULL)
	employee_remove(pArrayListEmployee);
return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno=-1;
	Employee* pAuxiliarEmployee;
	char buffername[128];
    if(pArrayListEmployee!=NULL)
    {
    	for (int i = 0; i <ll_len(pArrayListEmployee); ++i)//
    	{
			pAuxiliarEmployee=ll_get(pArrayListEmployee,i);
			employee_getNombre(pAuxiliarEmployee, buffername);
			printf("%d\t%-20s\t%d\t%d\n",employee_getRetId(pAuxiliarEmployee),buffername,
			employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));
		}
    	retorno=0;
    }
return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno=-1;
	//int orden=1;

	//int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
	//ll_sort(pArrayListEmployee, employee_Criterio_Short, orden);


return retorno;
}
int employee_Criterio_Short(LinkedList* pEployeeCero, LinkedList* pEplyeeUno)
{
	int retorno=-1;
	//void* p0;
	//void* p1;
	//pEployeeCero=p0;
	//pEplyeeUno=p1;
	//ll_get(pEployeeCero,0)=p0;
	//pEplyeeUno=ll_get(pEplyeeUno, 1)=p1;

return retorno;
}
//int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);
/*
int (*pFunc)(void* ,void*)
{

}
*/
/*
 * brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 * param param *char path de archivo y *pArrayListEmployee a LinkedList
 * return  0 si lo logro la carga y -1 si salio mal
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int estado=-1;
	char bufferName[128];
	FILE* pFileCsv;
	Employee* pAuxiliarEmployee;
	pFileCsv=fopen(path,"w");
	if(pFileCsv!=NULL&&path!=NULL&&pArrayListEmployee!=NULL)
	{
		fprintf(pFileCsv,"id,nombre,horasTrabajadas,sueldo\n");
		for (int i=0; i<ll_len(pArrayListEmployee); ++i)
		{
			pAuxiliarEmployee=ll_get(pArrayListEmployee, i);
			employee_getNombre(pAuxiliarEmployee,bufferName);
			fprintf(pFileCsv,"%d,%s,%d,%d\n",employee_getRetId(pAuxiliarEmployee),bufferName,
					employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));
		}
		fclose(pFileCsv);
		estado=0;
		puts("Se han Guardado los Cambios");
	}else
		 puts("No se ha podido inizilizar el archivo");

return estado;
}
/*
 * brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 * param param *char path de archivo y *pArrayListEmployee a LinkedList
 * return  0 si lo logro la carga y -1 si salio mal
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int estado=-1;
	FILE* pFileBin;
	Employee* pAuxiliarEmployee;
	pFileBin=fopen(path,"w");
	if(pFileBin!=NULL&&path!=NULL&&pArrayListEmployee!=NULL)
		{
			for (int i=0; i<ll_len(pArrayListEmployee); ++i)
			{
				pAuxiliarEmployee=ll_get(pArrayListEmployee, i);
				fwrite(pAuxiliarEmployee,sizeof(Employee),1,pFileBin);
			}
			fclose(pFileBin);
			estado=0;
			puts("Se han Guardado los Cambios");
		}else
			 puts("No se ha podido inizilizar el archivo");
	return estado;
}
/*
 * brief da la baja del programa
 * param *pArrayListEmployee a LinkedList estado de crag de archivo csv y bin
 * return 0 si todo bien y -1 si salio mal
 */
int controller_shotdown(LinkedList* listaEmpleados,int estadoBin,int estadoCsv)
{
	int retorno=-1;
	int opcion;
	if(listaEmpleados!=NULL)
	{
		pedirInt(&opcion,"PARA GUARDAR LOS CAMBIOS INGRESE UN NUMERO.\nSI NO DESEA GUARDAR INGRESE 10", "Ingrese un numero entre 1 y 10\n'10' PARA NO GUARDAR",MINIMO,MAXIMO,INTENTOS);
		if(opcion!=10)
			{
				if((estadoBin==0||estadoCsv==0))
					{
					controller_saveAsText("Midata.csv",listaEmpleados);
					controller_saveAsBinary("Midata.bin",listaEmpleados);
					puts("SE HA GURDADO TODA LA INFORMACION");
					}else
						puts("Se debe cargar la lista antes de poder grabar");
			}
		for (int i=0; i<ll_len(listaEmpleados); ++i)
		{
			free(ll_get(listaEmpleados,i));
		}
		ll_deleteLinkedList(listaEmpleados);
		retorno=0;
	}
return retorno;
}
/*
 * \brief Listar un empleados
 * \param lista linkenlist, posicion
 * \return 0 si todo bien y -1 si salio mal
 */
int controller_ListOneEmployee(LinkedList* pArrayListEmployee, int posicion)
{
    int retorno=-1;
	Employee* pAuxiliarEmployee;
	char buffername[128];
    if(pArrayListEmployee!=NULL)
    {
    	pAuxiliarEmployee=ll_get(pArrayListEmployee,posicion);
		employee_getNombre(pAuxiliarEmployee, buffername);
		printf("%d\t%-20s\t%d\t%d\n",employee_getRetId(pAuxiliarEmployee),buffername,
		employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));

    	retorno=0;
    }
return retorno;
}
