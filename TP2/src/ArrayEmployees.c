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
#include "Menu.h"
#include "Informes.h"

#define NOMINA_EMP 1000
#define OCUPADO 0
#define LIBRE -1
#define MINIMO 1
#define MAXIMO 5
#define INTENTOS 3
#define SALMIN 1000
#define SALMAX 500000

/**
 * \brief inicializa todas las posiciones del array como Libres pone la bander isEmpty en -1
 * \param  *plistEmployee recibo array por referencia, len tamaño del array
 * \return Retorna 0 si todo bien y -1 si no logro inicializar el array
 */
int initEmployees(eEmployee *plistEmployee,int len)
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
/**
 * brief Agrega en el array de empleados existente los valores recibidos como parámetro en la primer posición libre.
 * \param *plistEmployee recibo array por referencia, len tamaño del array, id, name[], lastName[], salary, sector
 * \return retona -1 si no pudo ser cargado el array o 0 si salio todo bien
 */
int addEmployee(eEmployee *plistEmployee,int len,int id,char name[],char lastName[],float salary,int sector)
{
	int estado=-1;
	int posicionLibre;
	if(plistEmployee!=NULL && len>0 && id>0 && salary>=SALMIN && salary<=SALMAX && strlen(name)>0 && strlen(lastName)>0 && sector>=1 && sector<=5)
		{
			posicionLibre=findFreePlace(plistEmployee, NOMINA_EMP);
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
/**
* \brief Busca un empleado recibiendo como parámetro de búsqueda su Id.
* \param  *plistEmployee recibo array por referencia,len tamaño del array, id
* \return Retorna la posicion en el array del id solicitado o -1 si el no exixte
*/
int findEmployeeById(eEmployee *plistEmployee,int len,int id)
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
/**
*  \brief Elimina de manera lógica con isEmpty Flag en -1 un empleado recibiendo como parámetro su Id.
* \param *plistEmployee recibo array por referencia,len tamaño del array, id
* \return retorna -1 si no pudo ser dado de baja y 0 si esta todo bien
*/
int removeEmployee(eEmployee *plistEmployee,int len,int id)
{
	int retorno=-1;
	int posicion;
	if(plistEmployee!=NULL && len>0 && id>=MINIMO && id<=NOMINA_EMP)
		 {
			posicion=findEmployeeById(plistEmployee, len, id);
			if(posicion>=0)
			{
			plistEmployee[posicion].isEmpty=LIBRE;
			retorno=0;
			printf("\nSe ha dado de baja al empleado %s\n\n",strcat(plistEmployee[posicion].name, plistEmployee[posicion].lastName));
			}else
			{
			puts("Ingrese ID Valido");
			}
			;
		 }
	return retorno;
}
/**
* \brief Ordena el array de empleados por apellido y sector de manera ascendente o descendente.
* \param *plistEmployee recibo array por referencia,len tamaño del array, order orden ascenedete o descenedente
* \return retorna -1 si no pudo ser ordenada la lista y 0 si esta todo ordenado
*/
int sortEmployees(eEmployee *plistEmployee,int len,int order)
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
/**
* \brief Imprime el arraay de empleados ocupados
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna 0 si se logor carga  y -1  si no
*/
int printEmployees(eEmployee *plistEmployee,int len)
{
		int estado=-1;
		int contadordeCargados=0;
		encabezadoLista();
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
		linea();
		estado=0;
	return estado;
}
/**
* \brief Modifica un ID ocupado dando la opcion a elegir los campos
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna -1 si no pudo hacer los cambios y 0 todo bien
*/
 int modifyOneEmploye(eEmployee *plistEmployee, int len)
 {
	 int retorno=-1;
	 int idamodificar;
	 int posicion;
	 int buffersSector;
	 char bufferLastName[51];
	 char bufferName[51];
	 float bufferSalary;
	 int opcion;
	 if(plistEmployee!=NULL && len>0)
		 {
		 printEmployees(plistEmployee, NOMINA_EMP);
		 pedirInt(&idamodificar, "Ingrese Id a modificar", "Error Ingrese Id valido", MINIMO, NOMINA_EMP, INTENTOS);
		 if(idamodificar>0 && idamodificar<NOMINA_EMP)
		 {
			 posicion=findEmployeeById(plistEmployee, NOMINA_EMP, idamodificar);
		 }
		 if (posicion>=0)
			 {
			 do
				 {
					 puts("INGRESE OPCION A MOFIFICAR");
					 imprimirMenuModificar();
					 pedirInt(&opcion, "INGRESE OPCION A MOFIFICAR", "Ingrese entre 1 y 5", MINIMO,MAXIMO,INTENTOS);
					 switch (opcion)
					 {
						case 1:
							if(pedirNombre(bufferName, sizeof(bufferName), "Ingrese Nombre", "Error El NOMBRE debe empezar con mayuscula y solo letras", INTENTOS)==0)
							{
								strncpy(plistEmployee[posicion].name, bufferName, sizeof(plistEmployee->name));
							}else
								puts("Hubo un problema con la carga, intentelo nuevamente");
							break;
						case 2:
							if(pedirNombre(bufferLastName, sizeof(bufferLastName), "Ingrese Apellido", "Error El Apellido debe empezar con mayuscula y solo letras", INTENTOS)==0)
							{
								strncpy(plistEmployee[posicion].lastName, bufferLastName, sizeof(plistEmployee->lastName));
							}else
								puts("Hubo un problema con la carga, intentelo nuevamente");
							break;
						case 3:
							if(pedirFloat(&bufferSalary, "Ingrese salario", "Ingrese monto valido entre 1000 y 500000", SALMIN, SALMAX, INTENTOS)==0)
							{
								plistEmployee[posicion].salary=bufferSalary;
							}else
								puts("Hubo un problema con la carga, intentelo nuevamente");
							break;
						case 4:
							if(pedirInt(&buffersSector, "Ingrese sector", "Opciones entre 1 y 5", MINIMO, MAXIMO, INTENTOS)==0)
							{
								plistEmployee[posicion].sector=buffersSector;
							}else
								puts("Hubo un problema con la carga, intentelo nuevamente");
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
 /**
 * \brief Realiza las operaciones necesarias sobre la variable salario para reportar total, promedio y cantidad sobre el promedio
 * \param *plistEmployee recibo array por referencia, len tamaño del array,
 * \param *totalSalary paso por referencia total de salrio, *promSalary paso por referncia promedio de salario,
 * \param *overProm paso por referencia la cantidad de empleados que cobran sobre el promedio
 * \return Retorna -1 si no pudo hacer los calculos y 0 todo bien
 */
 int operateSalaryEmployees(eEmployee *plistEmployee,int len)
 {
	 int retorno=-1;
	 float sumSalary=0;
	 int contSalary=0;
	 int contOverProm=0;
	 float promedioSal;
	 eEmployee employeesSobrePromedio[NOMINA_EMP];
	 if(plistEmployee!=NULL && len>0 && initEmployees(employeesSobrePromedio,NOMINA_EMP)==0)
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
		 for (int j=0; j< len; j++)
		 {
			 if(plistEmployee[j].salary>promedioSal)
			 {
				 employeesSobrePromedio[contOverProm]=plistEmployee[j];
				 contOverProm++;
			 }
		 }
		 printf("\n\nLa Suma de los salarios es %.2f\n\nEl Promedio de salarios %.2f\n\n"
		 "La cantidad de salarios que superan el promedio es %d\n\n",sumSalary,promedioSal,contOverProm);
		 if (contOverProm>0)
		 	 {
			  puts("La nomina de empleados que ganan mas que el promedio es la siguienrte");
			  printEmployees(employeesSobrePromedio,contOverProm);
		 	 }

		 retorno=0;
	}
	 return retorno;
 }
/**
* \brief busca el primer index del array con flag emty
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna lugar el primer lugar libre de la lista o -1 si no encuentra ninguno libre
*/
int findFreePlace(eEmployee *plistEmployee,int len)
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
/**
 * \brief busca cantidad de posiciones ocupadas en el array
* \param *plistEmployee recibo array por referencia, len tamaño del array
* \return Retorna cantidad de lugares o -1 si no encuentra ninguno lugar ocupados
 */
int listlong(eEmployee *plistEmployee,int len)
{
	int retorno=-1;
	int contBusy=0;
	if(plistEmployee!=NULL && len>0)
	{
		for (int i=0;i<len;++i)
		{
			if(plistEmployee[i].isEmpty==OCUPADO)
			{
				contBusy++;
			}
		}
		if(contBusy>0)
		{
			retorno=contBusy;
		}
	}
	return retorno;
}
