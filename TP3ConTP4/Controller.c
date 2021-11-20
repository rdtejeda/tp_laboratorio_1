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
#define CERO 0

/*
 * brief Carga los datos de los empleados desde el archivo *.csv (modo texto).
 * param *char path de archivo y *pLinkedListEmpleados a LinkedList
 * return 0 si lo logro la carga y -1 si salio mal
 */
int controller_loadFromText(char* path , LinkedList* pLinkedListEmpleados)
{
	int retorno=-1;
	if(path!=NULL && pLinkedListEmpleados!=NULL)
		{
		FILE* pFileCsv;
		pFileCsv=fopen(path,"r");
		if(pFileCsv!=NULL)
			{
				parser_EmployeeFromText(pFileCsv,pLinkedListEmpleados);
				fclose(pFileCsv);
				retorno=0;
				puts("La lista se ha cargado desde el *.csv");
			}else
				puts("El archivo CSV no exciste");
		}else
			puts("Parametros erroneos");
return retorno;
}
/*
 * brief Carga los datos de los empleados desde el archivo *.bin (modo binario).
 * param param *char path de archivo y *pLinkedListEmpleados a LinkedList
 * return 0 si lo logro la carga y -1 si salio mal
 */
int controller_loadFromBinary(char* path , LinkedList* pLinkedListEmpleados)
{
	int estado=-1;
	if(path!=NULL && pLinkedListEmpleados!=NULL)
	{
		FILE* pFileBin;
		pFileBin=fopen(path,"r");
		if(pFileBin!=NULL)
				{
					parser_EmployeeFromBinary(pFileBin, pLinkedListEmpleados);
					fclose(pFileBin);
					puts("La lista se ha cargado desde el *.bin");
					estado=0;
				}else
					puts("El archivo Binario no exciste");
	}else
		puts("Parametros erroneos");
return estado;
}
/*
 * brief da el alta a un empleado
 * param pLinkedListEmpleados LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_addEmployee(LinkedList* pLinkedListEmpleados)
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
	if(pLinkedListEmpleados!=NULL)
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
			if(!ll_add(pLinkedListEmpleados,bufferEmployee))
				{
				puts("Se ha dado de alta al siguiente empleado");
				controller_ListOneEmployee(pLinkedListEmpleados, ll_indexOf(pLinkedListEmpleados, bufferEmployee));
				retorno=0;
				}else
				puts("No se ha podio agrega a la lista");
			}else
				puts("No se ha podido agregar a la lista");
	}else
		puts("La lista no esta iniciada");
return retorno;
}

/** \brief Modificar datos de empleado
 * \param pLinkedListEmpleados LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_editEmployee(LinkedList* pLinkedListEmpleados)
{
	int retorno=-1;
	if(pLinkedListEmpleados!=NULL&&ll_len(pLinkedListEmpleados)>0)
		{
			employee_modify(pLinkedListEmpleados);
			retorno=0;
		}else
			puts("No se puede Editar ya que La Lista esta vacía");
return retorno;
}

/** \brief Elimina datos de empleado
 * \param pLinkedListEmpleados LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_removeEmployee(LinkedList* pLinkedListEmpleados)
{
	int retorno=-1;
	if(pLinkedListEmpleados!=NULL&&ll_len(pLinkedListEmpleados)>0)
	{
		employee_remove(pLinkedListEmpleados);
		retorno=0;
	}else
	puts("No se puede Eliminar ya que La Lista esta vacía");
return retorno;
}

/** \brief Listar empleados
 * \param pLinkedListEmpleados LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_ListEmployee(LinkedList* pLinkedListEmpleados)
{
    int retorno=-1;
	Employee* pAuxiliarEmployee;
	char buffername[128];
    if(pLinkedListEmpleados!=NULL)
    {
    	if(ll_len(pLinkedListEmpleados)>0)
    	{
    		imprimirEncabezado();
    		for (int i = 0; i <ll_len(pLinkedListEmpleados); ++i)//
			{
				pAuxiliarEmployee=ll_get(pLinkedListEmpleados,i);
				employee_getNombre(pAuxiliarEmployee, buffername);
				printf("%d\t%-20s\t%d\t%d\n",employee_getRetId(pAuxiliarEmployee),buffername,
				employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));
			}
			retorno=0;
    	}else
    		puts("No se puede Listar ya que La Lista esta vacía");
    }
return retorno;
}

/** \brief Ordenar empleados
 * \param pLinkedListEmpleados LinkedList*
 * \return 0 si lo logro la carga y -1 si salio mal
 */
int controller_sortEmployee(LinkedList* pLinkedListEmpleados)
{
	int retorno=-1;
	int orden=1;
	int criterio;
	int (*pEmplyeeOrder)(void*,void*);
	if(pLinkedListEmpleados!=NULL)
	{
		if(ll_len(pLinkedListEmpleados)>1)
		{
			puts("SELECCIONE CRITERIO DE ORDENAMIENTO");
			criterio=menuCriterio();
			switch(criterio)
				{
					case 1:
						pEmplyeeOrder=employee_Criterio_ShortByName;
						break;
					case 2:
						pEmplyeeOrder=employee_Criterio_ShortByHoras;
						break;
					case 3:
						pEmplyeeOrder=employee_Criterio_ShortBySueldo;
						break;
					case 4:
						pEmplyeeOrder=employee_Criterio_ShortByID;
						break;
					default:
						break;
				}
			pedirInt(&orden, "De MAYOR a MENOR Ingrese '0'- De MENOR a MAYOR Ingrese '1'","ERROR-Ingrese 0 ó 1",CERO,MINIMO,INTENTOS);
			ll_sort(pLinkedListEmpleados, pEmplyeeOrder, orden);
			puts("LA LISTA HA SIDO ORDENADA");
			controller_ListEmployee(pLinkedListEmpleados);
			retorno=0;
		}else
		     puts("Para poder ordenar la lista debe tener mas de un Empleado");
	}
return retorno;
}
/*
 * brief Guarda los datos de los empleados en el archivo *.csv (modo texto).
 * param param *char path de archivo y *pLinkedListEmpleados a LinkedList
 * return  0 si lo logro la carga y -1 si salio mal
 */
int controller_saveAsText(char* path , LinkedList* pLinkedListEmpleados)
{
	int estado=-1;
	char bufferName[128];
	int paso=0;
	FILE* pFileCsv;
	Employee* pAuxiliarEmployee;
	pFileCsv=fopen(path,"w");
	if(pFileCsv!=NULL&&path!=NULL&&pLinkedListEmpleados!=NULL)
	{
		fprintf(pFileCsv,"id,nombre,horasTrabajadas,sueldo\n");
		for (int i=0; i<ll_len(pLinkedListEmpleados); ++i)
		{
			pAuxiliarEmployee=ll_get(pLinkedListEmpleados, i);
			employee_getNombre(pAuxiliarEmployee,bufferName);
			paso++;
			fprintf(pFileCsv,"%d,%s,%d,%d\n",employee_getRetId(pAuxiliarEmployee),bufferName,
					employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));
		}
		fclose(pFileCsv);
		estado=0;
		printf("Se han guardado en el archivo %d empleados\n",paso);
	}else
		 puts("No se ha podido inizilizar el archivo");

return estado;
}
/*
 * brief Guarda los datos de los empleados en el archivo *.bin (modo binario).
 * param param *char path de archivo y *pLinkedListEmpleados a LinkedList
 * return  0 si lo logro la carga y -1 si salio mal
 */
int controller_saveAsBinary(char* path , LinkedList* pLinkedListEmpleados)
{
	int estado=-1;
	FILE* pFileBin;
	Employee* pAuxiliarEmployee;
	pFileBin=fopen(path,"w");
	if(pFileBin!=NULL&&path!=NULL&&pLinkedListEmpleados!=NULL)
		{
			for (int i=0; i<ll_len(pLinkedListEmpleados); ++i)
			{
				pAuxiliarEmployee=ll_get(pLinkedListEmpleados, i);
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
 * brief da la baja del programa chequea el grabdo final y elimina la LinkedList
 * param *pLinkedListEmpleados a LinkedList estado de crag de archivo csv y bin
 * return 0 si todo bien y -1 si salio mal
 */
int controller_shotdown(LinkedList* pLinkedListEmpleados,int estadoBin,int estadoCsv)
{
	int retorno=-1;
	int opcion;
	int opciondos;
	if(pLinkedListEmpleados!=NULL)
	{
		pedirInt(&opcion,"PARA SALIR SIN GRABAR INGRESA '1'.\nSI DESEAS GRABAR LOS CAMBIOS INGRESA '10'", "ERROR-Para Salir sin Grabar Ingrese 1 a 9\nPARA GUARDAR Ingresa 10",MINIMO,MAXIMO,INTENTOS);
		if(opcion==10)
			{
				if((estadoBin==0||estadoCsv==0))
					{
					controller_saveAsText("data.csv",pLinkedListEmpleados);
					controller_saveAsBinary("data.bin",pLinkedListEmpleados);
					puts("SE HA GURDADO TODA LA INFORMACION");
					}else
						{
							puts("CUIDADO - No se ha cargado la lista desde archivo");
							puts("Si guarda sin Cargar el Archivo Se perdera el contenido del mismo");
							puts("Para Cargar la lista del archivo y luego Grabar ingrese '1' - (SE CARGARA LA LISTA DESDE EL ARCHIVO Y GRABARA)");
							puts("Para Grabar sin cargar el archivo ingrese '2' - (CUIDADO SOLO SE GRABARA LA LISTA ACTUAL)");
							puts("Para salir sin grabar ingrese '3' - (CUIDADO SE PERDERA LA LISTA ACTUAL");
							pedirInt(&opciondos,"Ingrese OPCION","ERROR-Ingrese entre 1 y 3",MINIMO,INTENTOS,INTENTOS);
							if(opciondos==1)
							{
								controller_loadFromText("data.csv",pLinkedListEmpleados);
								controller_saveAsText("data.csv",pLinkedListEmpleados);
								controller_saveAsBinary("data.bin",pLinkedListEmpleados);
								puts("SE HA GURDADO TODA LA INFORMACION");
							}else if(opciondos==2)
							{
								controller_saveAsText("data.csv",pLinkedListEmpleados);
								controller_saveAsBinary("data.bin",pLinkedListEmpleados);
							}else
								puts("SE PERDIDO LA LISTA ACTUAL");

						}
				//fcloseall();
			}
	ll_deleteLinkedList(pLinkedListEmpleados);

	retorno=0;
	}
return retorno;
}
/*
 * \brief Listar un empleados
 * \param lista linkenlist, posicion
 * \return 0 si todo bien y -1 si salio mal
 */
int controller_ListOneEmployee(LinkedList* pLinkedListEmpleados, int posicion)
{
    int retorno=-1;
	Employee* pAuxiliarEmployee;
	char buffername[128];
    if(pLinkedListEmpleados!=NULL && posicion>=0)
    {
    	imprimirEncabezado();
    	pAuxiliarEmployee=ll_get(pLinkedListEmpleados,posicion);
		employee_getNombre(pAuxiliarEmployee, buffername);
		printf("%d\t%-20s\t%d\t%d\n",employee_getRetId(pAuxiliarEmployee),buffername,
		employee_getRetHorasTrabajadas(pAuxiliarEmployee),employee_getRetSueldo(pAuxiliarEmployee));

    	retorno=0;
    }
return retorno;
}
//========================================================================================================
/*
 * brief cuenta los empleados en el archivo *.csv (modo texto).
 * param *char path de archivo
 * return cantidad de empleados si lo logro la carga y -1 si salio mal
 */
int controller_countEmployeeFromText(char* path)
{
	int retorno=-1;
	if(path!=NULL)
		{
		FILE* pFileCsv;
		pFileCsv=fopen(path,"r");
		if(pFileCsv!=NULL)
			{
				retorno=parser_countEmployeeFromText(pFileCsv);
				fclose(pFileCsv);
			}else
				puts("El archivo CSV no exciste");
		}else
			puts("Parametros erroneos");
return retorno;
}
/*
 * brief cuenta los empleados desde el archivo *.bin (modo binario).
 * param param *char path
 * return cantidad de empleados si lo logro la carga y -1 si salio mal
 */
int controller_countEmployeeFromBinary(char* path)
{
	int estado=-1;
	if(path!=NULL)
	{
		FILE* pFileBin;
		pFileBin=fopen(path,"r");
		if(pFileBin!=NULL)
				{
					estado=parser_countEmployeeFromBinary(pFileBin);
					fclose(pFileBin);

				}else
					puts("El archivo Binario no exciste");
	}else
		puts("Parametros erroneos");
return estado;
}
//==============================================================================================================
