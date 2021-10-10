/*
 *  ArrayEmployees.c
 *  Created on: 7 oct. 2021
 *  Author: Tejeda Roberto
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>

#include "ArrayEmployees.h"
#include "Pedir.h"

#define NOMINA_EMP 10
#define OCUPADO 0 //isEmpty flag OCUPADA O LLENA
#define LIBRE -1  //isEmpty flag
#define MINIMO 0
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 100000
#define SALMAX 500000

//=============================================================================
// 2.1 Función initEmployees
/** \brief inicializa todas las posiciones del array como Libres
 * esta fiuncion pone la bander isEmpty en -1 para todos las posiciones del array
 * \param list *pEmployee del array Employee
 * \param len int largo del Array
 * \return Retorna 0 si todo bien  y -1 si no
 */
int initEmployees(eEmployee plistEmployee[],int len)
{
	int estado=-1;
	   if (plistEmployee!=NULL && len>0)
	   {
		  for (int j = 0;  j<len; j++)
		   {
			  plistEmployee[j].isEmpty=LIBRE;
			  estado=0;
		   }
	   }
	   return estado;
}
//=============================================================================
//2.2 Función addEmployees
//Agrega en un array de empleados existente los valores recibidos como parámetro en la primer
//posición libre.
/** \brief add in a existing list of employees the values received as parameters
 * in the first empty position
 * \param list employee*
 * \param len int
 * \param id int
 * \param name[] char
 * \param lastName[] char
 * \param salary float
 * \param sector int
 * \return int Return (-1) if Error [Invalid length or NULL pointer or without
free space] - (0) if Ok
 */
int addEmployee(eEmployee plistEmployee[],int len,int id,char name[],char lastName[],float salary,int sector)
{
	int estado=-1;
	int posicionLibre;
	if(plistEmployee!=NULL && len>0 && id>0 && salary>SALMIN && salary<SALMAX && strlen(name)>0 && strlen(lastName)>0 && sector>=1 && sector<=5)
		{
			posicionLibre=buscarLugarLibre(plistEmployee, NOMINA_EMP);
			if(posicionLibre>=0)
				{
				plistEmployee[posicionLibre].id=id;
				plistEmployee[posicionLibre].salary=salary;
				plistEmployee[posicionLibre].sector=sector;
				strncpy(plistEmployee[posicionLibre].lastName, lastName, sizeof(plistEmployee[posicionLibre].lastName));
				strncpy(plistEmployee[posicionLibre].name, name, sizeof(plistEmployee[posicionLibre].name));
				plistEmployee[posicionLibre].isEmpty=OCUPADO;
				estado=0;
				}
		}else
		{
			puts("La carga no fue posible, intentelo nuevamente");
		}
   return estado;
}
//Ejemplo uso: r = addEmployee(arrayEmployees, ELEMENTS,id,name,lastName,salary,sector);
//==============================================================================
/*
 2.3 Función findEmployeeById
Busca un empleado recibiendo como parámetro de búsqueda su Id.
*/

/** \brief find an Employee by Id en returns the index position in array.
* \param list Employee*
* \param len int
* \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL
pointer received or employee not found]
*/
int findEmployeeById(eEmployee plistEmployee[],int len,int id)
{
	int retorno=-1;
		if(plistEmployee!=NULL && len>0)
		{
			for (int i=0;i<len;++i)
			{
				if(plistEmployee[i].id==id && plistEmployee[i].isEmpty==OCUPADO)
				{
					retorno=i;
					break;
				}
			}
		}
		return retorno;
}
// Ejemplo uso: int index = findEmployeeById(arrayEmployees, ELEMENTS,9);
//=============================================================================
//2.4 Función removeEmployee Elimina de manera lógica (isEmpty Flag en 1) un empleado recibiendo como parámetro su Id.
/** \brief Remove a Employee by Id (put isEmpty Flag in 1)
*
* \param list Employee*
* \param len int
* \param id int
* \return int Return (-1) if Error [Invalid length or NULL pointer or if can't
find a employee] - (0) if Ok
*/
int removeEmployee(eEmployee plistEmployee[],int len,int id)
{
	int retorno=-1;
	int posicion;
	posicion=findEmployeeById(plistEmployee, len, id);
	if(plistEmployee!=NULL && len>0)
		 {
			if(posicion==0)
			{
			plistEmployee[posicion].isEmpty=LIBRE; // podemos hacer un estados de baja para llevar un control
			retorno=0;
			}else
			{
			puts("Ingrese ID Valido");
			}

		 }
	return retorno;
}
//Ejemplo uso: r = removeEmployee(arrayEmployees, ELEMENTS,20);
//=============================================================================
//2.5 Función sortEmployees Ordena el array de empleados por apellido y sector de manera ascendente o descendente.
/** \brief Sort the elements in the array of employees, the argument order
indicate UP or DOWN order
*
* \param list Employee*
* \param len int
* \param order int [1] indicate UP - [0] indicate DOWN
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int sortEmployees(eEmployee plistEmployee[],int len,int order)
{
	int banderaSwapp=-1;
	eEmployee auxiliar;
	int limite=len;
	int estadostrcmp;
	if(plistEmployee!=NULL && len>0)
		{
			do
			{
				banderaSwapp=0;
				limite=limite-1;
				for (int i=0; i<limite; i++)
				{
				estadostrcmp=strcmp(plistEmployee[i].lastName, plistEmployee[i+1].lastName);
				switch(order)
					{
					case 1:
						if(estadostrcmp>0)
						{
							banderaSwapp=1;
							auxiliar=plistEmployee[i];
							plistEmployee[i]=plistEmployee[i+1];
							plistEmployee[i+1]=auxiliar;
						}
						if (estadostrcmp==0)
						{
							if(plistEmployee[i].sector>plistEmployee[i+1].sector)
							{
								banderaSwapp=1;
								auxiliar=plistEmployee[i];
								plistEmployee[i]=plistEmployee[i+1];
								plistEmployee[i+1]=auxiliar;
							}
						}
						break;
					case 2:
						if(estadostrcmp<0)
						{
							banderaSwapp=1;
							auxiliar=plistEmployee[i];
							plistEmployee[i]=plistEmployee[i+1];
							plistEmployee[i+1]=auxiliar;
						}
						if (estadostrcmp==0)
						{
							if(plistEmployee[i].sector<plistEmployee[i+1].sector)
							{
								banderaSwapp=1;
								auxiliar=plistEmployee[i];
								plistEmployee[i]=plistEmployee[i+1];
								plistEmployee[i+1]=auxiliar;
							}
						}
						break;
					default:
						break;
					}
				}
			}while(banderaSwapp==1);
		}
		return banderaSwapp;
}
//=============================================================================
//2.6 Función printEmployees
/**
* \brief Imprime todo el arraay de Employee
* \param recibe un estructura por puntero y el largo
* \return Retorna 0 si se logor carga  y -1  si no
*/
int printEmployees(eEmployee plistEmployee[],int len)
{
	int estado=-1;
		int contadordeCargados=0;
		printf("==============================================================================\n");
		printf("Id Name\t\t\tLastName\t\tSalary\t   Sector\tIsEmty\n");
		printf("==============================================================================\n");
		if (plistEmployee!=NULL && len>0)
		{
			for (int i= 0;  i< len; i++)
			{
				if(plistEmployee[i].isEmpty==OCUPADO)
				{
					printf("%2d %-20s %-23s %2.2f %6d %8d\n",
					plistEmployee[i].id,plistEmployee[i].name,plistEmployee[i].lastName,plistEmployee[i].salary,plistEmployee[i].sector,plistEmployee[i].isEmpty);
					contadordeCargados++;
				}
			}
			if(contadordeCargados==0)
				{
					puts("NO HAY DIPLAYS CARGADOS");
				}
		}
		printf("==============================================================================\n");
		estado=0;
		return estado;
}
//==============================================================================

/**
* \brief Modifica un ID emty
* \param recibe un estructura por puntero, el largo
* \return Retorna -1 todo mal 0 todo bien
*/
 int modifyOneEmploye(eEmployee plistEmployee[], int len)
 {
	 int retorno=-1;
	 int idamodificar;
	 int posicion;
	 int buffersSector;
	 char bufferLastName[51];
	 char bufferName[51];
	 float bufferSalary;
	 int opcion;
	 eEmployee auxiliar; //= {1,100,99,"Name","Siempre 11 viva",0}; //MODIFICACION Harcodeada
	 if(plistEmployee!=NULL && len>0)
		 {
		 printEmployees(plistEmployee, NOMINA_EMP); // IMPRIMIR LISTA EMTY - MOSTRA LISTADO de posibles Display a modificar
		 pedirInt(&idamodificar, "Ingrese Id a modificar", "Error Ingrese Id valido", 1, NOMINA_EMP, INTENTOS);// Seleccionar id a modificar
		 posicion=findEmployeeById(plistEmployee, NOMINA_EMP, idamodificar); // Buscar la posicion en el array del id selecionado
		 if (posicion>=0)// Modificar la pantalla
			 {
			 do
				 {
					 puts("INGRESE OPCION A MOFIFICAR");
					 imprimirMenuModificar();
					 pedirInt(&opcion, "INGRESE OPCION A MOFIFICAR", "Ingrese entre 1 y 5", 1,5,INTENTOS);
					 switch (opcion)
					 {
						case 1:
							pedirText(bufferName, sizeof(auxiliar.name), "Ingrese Nombre", "Ingrese Nombre valido",INTENTOS);
							strncpy(plistEmployee->name, bufferName, sizeof(plistEmployee->name));
							break;
						case 2:
							pedirText(bufferLastName, sizeof(auxiliar.lastName), "Ingrese Apellido", "Ingrese Apellido valido", INTENTOS);
							strncpy(plistEmployee->lastName, bufferLastName, sizeof(plistEmployee->lastName));
							break;
						case 3:
							pedirFloat(&bufferSalary, "Ingrese salario", "Ingrese monto valido", SALMIN, SALMAX, INTENTOS);
							plistEmployee->salary=bufferSalary;
							break;
						case 4:
							pedirInt(&buffersSector, "Ingrese sector", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS);
							plistEmployee->sector=buffersSector;
							break;
						default:
							break;
					 }
					 printEmployees(plistEmployee, NOMINA_EMP);
				 }while(opcion<5);
			 }else
				 puts("Id no hallado");
		 }
	 return retorno;
 }
 //=============================================================================

 int operateSalaryEmployees(eEmployee plistEmployee[],int len,float *totalSalary, float *promSalary, int *overProm)
 {
	 int retorno=-1;
	 float sumSalary=0;
	 int contSalary=0;
	 int contOverProm=0;
	 float promedioSal;
	 if(plistEmployee!=NULL && len>0)
	 {
		 for (int i=0; i<len; i++)
		 {
			 if(plistEmployee[i].isEmpty==OCUPADO)
			 {
			 sumSalary=plistEmployee[i].salary+sumSalary;
			 contSalary++;
			 }
		 }
		  promedioSal=sumSalary/contSalary;
		 *promSalary=promedioSal;
		 for (int j=0; j< len; j++)
		 {
			 if(plistEmployee[j].salary>promedioSal)
			 {
			 contOverProm++;
			 }
		 }
		 *totalSalary=sumSalary;
		 *overProm=contOverProm;
		 //totalSalary=sumSalary;
		// printf("\nSuma de salarios %.2f, cantidad de salarios %d y promedio de salarios %.2f\n", sumSalary, contSalary, promSalary);
	 }
	 return retorno;
 }
//=============================================================================
/**
  * \brief me da un id consecutivo y no repetido memorizando el ultimolvalor
  * \param void
  * \return Retorna 0 si todo bien  y -1 si no numero de id
  */
int dameUnIdNuevo()
{
	static int contador=0;
	contador++;
	return contador;
}
//==============================================================================
/**
* \brief busca el primer index del array con flag emty
* \param recibe un estructura por puntero y el largo
* \return Retorna lugar el primer lugar libre de la lista o -1 si no encuentra ninguno libre
*/
int buscarLugarLibre(eEmployee plistEmployee[],int len)
{
	int retorno=-1;
	if(plistEmployee!=NULL && len>0)
	{
		for (int i=0;i<len;++i)
		{
			if(plistEmployee[i].isEmpty==LIBRE)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
//===========================================================================
