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
#include "Menu.h"
#define MINIMO 1
#define MAXIMO 10
#define INTENTOS 3
#define MAXIMOHORAS 300
#define MAXIMOSUELDO 500000

/**
* \brief reserva de forma dinamica memoria para un dato tipo Employee
* \param es void
* \return Retorna *pEmployee a direcion de memoria reservada
*/
Employee* employee_new()
{
	Employee* pEmployee=(Employee*)malloc(sizeof(Employee));
	if(pEmployee==NULL)
		puts("No se ha podido reservar espacio en memoria");

return pEmployee;
}
//===============================================================================================
/**
* \brief Realiza un *pEmployee, carga los valores en todos los campos de una entidad Employee
* \param es recibe puntero a char de los cuatro campos
* \return Retorna *pEmployee a direcion de memoria reservada
*/
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
	Employee* pEmployee=employee_new();

	if(pEmployee!=NULL && idStr!=NULL&& nombreStr!=NULL && horasTrabajadasStr!=NULL)
	{
		if(employee_setIdChar(pEmployee,idStr)!=0||employee_setSueldoChar(pEmployee,sueldoStr)!=0||
		employee_setHorasTrabajadasChar(pEmployee,horasTrabajadasStr)!=0||employee_setNombre(pEmployee,nombreStr)!=0)
		{
			puts("No se han podio setear los parametros ");
			employee_delete(pEmployee);
		}
	}else
			puts("No se ha podido crear nuevo entidad");
return pEmployee;
}
//===================================================================================================
/**
* \brief libera memoria reservada de forma dinamica que no pudo ser utilizada
* \param *pEmployee
* \return es void
*/
void employee_delete(Employee* pEmployee)
{
	if(pEmployee!=NULL)
	free(pEmployee);
}
//==================================================================================================
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Id
* \param es recibe *listEmployees e id buscado
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_findById(LinkedList* listEmployees, int id)
{
	int retorno=-1;
	int posicion;
	int largoLista;
	Employee* pAuxiliarEmployee;
	if(listEmployees!=NULL && id>0)
		{
		largoLista=ll_len(listEmployees);
		for (int i = 0; i < largoLista; i++)
			{
				pAuxiliarEmployee=ll_get(listEmployees, i);
				if(pAuxiliarEmployee->id==id)
				{
					posicion=i;
					break;
				}
			}
		}
	retorno=posicion;
return retorno;
}
//==================================================================================================
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Id
* \param es recibe *listEmployees e id buscado
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_modify(LinkedList* listEmployees)
{
	int retorno=-1;
	int posicion;
	int opcion;
	char bufferNombre[128];
	int bufferHorasTrabajadas;
	int bufferSueldo;
		if(listEmployees!=NULL)
			{
			posicion=employee_findPositionBy(listEmployees);
			printf("%d\n",posicion);
			if(posicion>=0)
				{
				puts("El empleado selecionado es");
				controller_ListOneEmployee(listEmployees, posicion);
				do
					{
					opcion=menuEdicion();
					switch(opcion)
						{
						case 1:
							pedirNombre(bufferNombre, sizeof(bufferNombre),"Ingres nuevo nombre","Nombre invalido", INTENTOS);
							employee_setNombre(ll_get(listEmployees, posicion),bufferNombre);
							puts("Su modificacion es");
							controller_ListOneEmployee(listEmployees, posicion);
							break;
						case 2:
							pedirInt(&bufferHorasTrabajadas,"Ingres Horas Trabajadas","Error ingrese entre 1 y 200",MINIMO,MAXIMOHORAS,INTENTOS);
							employee_setHorasTrabajadas(ll_get(listEmployees, posicion),bufferHorasTrabajadas);
							puts("Su modificacion es");
							controller_ListOneEmployee(listEmployees, posicion);
							break;
						case 3:
							pedirInt(&bufferSueldo,"Ingres Sueldo","Error ingrese monto valido",MINIMO,MAXIMOSUELDO,INTENTOS);
							employee_setSueldo(ll_get(listEmployees, posicion),bufferSueldo);
							puts("Su modificacion es");
							controller_ListOneEmployee(listEmployees, posicion);
							break;
						}
					}while(opcion!=4);
				retorno=0;
				}
			}
return retorno;
}
//==================================================================================================
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Nombre de empleado
* \param es recibe *listEmployees e array de char name
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_findByName(LinkedList* listEmployees, char name[])
{
	int retorno=-1;
	int posicion;
	int largoLista;
	Employee* pAuxiliarEmployee;
	if(listEmployees!=NULL && name!=NULL)
		{
		largoLista=ll_len(listEmployees);
		for (int i = 0; i < largoLista; i++)
			{
				pAuxiliarEmployee=ll_get(listEmployees, i);
				if(!strcmp(pAuxiliarEmployee->nombre,name))
				{
					posicion=i;
					retorno=posicion;
					break;
				}
			}
		puts("El Nombre no fue encontrado");
		}
return retorno;
}
//======================================================================================================
/**
* \brief setea valor de Id en una entidad *Employee
* \param *pEmployee y valor Id
* \return o si lo logro y -1 todo mal
*/
int employee_setId(Employee* this,int id)
{
 int retorno=-1;
 if(this!=NULL&&id>=0)
	 {
		 this->id=id;
		 retorno=0;
	 }
 return retorno;
}
//=============================================================================================================
/**
* \brief setea valor de Id en una entidad *Employee
* \param *pEmployee y *id char
* \return 0 si lo logro y -1 todo mal
*/
int employee_setIdChar(Employee* this,char* id)
{
 int retorno=-1;
 if(this!=NULL && id!=NULL && esNumericaInt(id)==0)
	 {
		 this->id=atoi(id);
		 retorno=0;
	 }
 return retorno;
}
//=============================================================================================================
/**
* \brief entrega el valor de Id en una entidad *Employee
* \param *pEmployee y *id int
* \return 0 si lo logro y -1 todo mal
*/
int employee_getId(Employee* this,int* id)
{
int retorno=-1;
if(this!=NULL && id!=NULL)
	{
		*id=this->id;
		retorno=0;
	}

return retorno;
}
//=============================================================================================================
/**
* \brief entrega el valor de Id en una entidad *Employee
* \param *pEmployee
* \return id si lo logro y -1 todo mal
*/
int employee_getRetId(Employee* this)
{
int retorno=-1;
if(this!=NULL)
	{

		retorno=this->id;
	}

return retorno;
}
//====================================================================================
/**
* \brief setea valor de nombre en una entidad *Employee
* \param *pEmployee y *nombre char
* \return 0 si lo logro y -1 todo mal
*/
int employee_setNombre(Employee* this,char* nombre)
{
int retorno=-1;
if(this!=NULL && nombre!=NULL &&esAlfabetica(nombre)==0)
	{
		strncpy(this->nombre,nombre,sizeof(this->nombre));
		retorno=0;
	}
return retorno;
}
//========================================================================================
/**
* \brief entrega el valor de nombre deuna entidad *Employee
* \param *pEmployee y *nombre chart
* \return 0 si lo logro y -1 todo mal
*/
int employee_getNombre(Employee* this,char* nombre)
{
int retorno=-1;
if(this!=NULL&&nombre!=NULL)
{
	strcpy(nombre,this->nombre);
	retorno=0;
}

return retorno;
}
//=================================================================================
/**
* \brief setea valor de horas trabajadas en una entidad *Employee
* \param *pEmployee y valor horasTrabajadas
* \return o si lo logro y -1 todo mal
*/
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
int retorno=-1;
if(this!=NULL&&horasTrabajadas>0)
	{
		this->horasTrabajadas=horasTrabajadas;
		retorno=0;
	}
return retorno;
}
//===================================================================================
/**
* \brief setea valor de horas trabajadas en una entidad *Employee
* \param *pEmployee y *horatrabajadas char
* \return 0 si lo logro y -1 todo mal
*/
int employee_setHorasTrabajadasChar(Employee* this,char* horasTrabajadas)
{
 int retorno=-1;
 if(this!=NULL && horasTrabajadas!=NULL && esNumericaInt(horasTrabajadas)==0)
	 {
		 this->horasTrabajadas=atoi(horasTrabajadas);
		 retorno=0;
	 }
 return retorno;
}
//===================================================================================
/**
* \brief devuelve por puntero las horas trabajadas de una entidad *Employee
* \param *pEmployee y *horastrabajadas
* \return 0 si lo logro y -1 todo mal
*/
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
int retorno=-1;
if(this!=NULL&&horasTrabajadas!=NULL)
{
	*horasTrabajadas=this->horasTrabajadas;
	retorno=0;
}

return retorno;
}
//===================================================================================
/**
* \brief devuelve las horas trabajadas de una entidad *Employee
* \param *pEmployee
* \return horastrabjadas si lo logro y -1 todo mal
*/
int employee_getRetHorasTrabajadas(Employee* this)
{
int retorno=-1;
if(this!=NULL)
{
	retorno=this->horasTrabajadas;
}

return retorno;
}
//=================================================================================
/**
* \brief setea valor de sueldo en una entidad *Employee
* \param *pEmployee y valor sueldo
* \return o si lo logro y -1 todo mal
*/
int employee_setSueldo(Employee* this,int sueldo)
{
int retorno=-1;
if(this!=NULL&&sueldo>0)
	{
	this->sueldo=sueldo;
	retorno=0;
	}

return retorno;
}
//===================================================================================
/**
* \brief setea valor de sueldo en una entidad *Employee
* \param *pEmployee y *sueldo char
* \return 0 si lo logro y -1 todo mal
*/
int employee_setSueldoChar(Employee* this,char* sueldo)
{
 int retorno=-1;
 if(this!=NULL && sueldo!=NULL && esNumericaInt(sueldo)==0)
	 {
		 this->sueldo=atoi(sueldo);
		 retorno=0;
	 }
 return retorno;
}
//===================================================================================
/**
* \brief devuelve por puntero el sueldo de una entidad *Employee
* \param *pEmployee y *sueldo
* \return 0 si lo logro y -1 todo mal
*/
int employee_getSueldo(Employee* this,int* sueldo)
{
int retorno=-1;
if(this!=NULL&&sueldo!=NULL)
	{
		*sueldo=this->sueldo;
		retorno=0;
}
return retorno;
}
//===================================================================================
/**
* \brief devuelve el sueldo de una entidad *Employee
* \param *pEmployee
* \return sueldo si lo logro y -1 todo mal
*/
int employee_getRetSueldo(Employee* this)
{
int retorno=-1;
if(this!=NULL)
	{
		retorno=this->sueldo;
	}
return retorno;
}
//=================================================================
/**
  * \brief me da un id consecutivo y no repetido memorizando el ultimolvalor
  * \param void
  * \return Retorna nuevo id si todo bien  y -1 si no lofro
  */
int dameUnIdNuevoEmployee(void)
{
	//TEMPORAL
	/*
	int* id;
	int bufferint=1000;
	int cantidadt;
	id=&bufferint;
	FILE* pFileBinTemp;
	pFileBinTemp=fopen("UltimoId.bin","w");
	if(pFileBinTemp!=NULL)
		{
			cantidadt=fwrite(id,sizeof(int),1,pFileBinTemp);
			printf("Cantidad de fwrite dice %d\n",cantidadt);
			fclose(pFileBinTemp);
		}else
				 puts("No se ha podido inizilizar el archivo");
	*/
	//TEMPORAL
	int estado=-1;
	int bufferId;
	int* contador;
	contador=&bufferId;
	FILE* pFileBin;
	pFileBin=fopen("UltimoId.bin","r");
	if(pFileBin!=NULL)
		{
			fread(contador,sizeof(int),1,pFileBin);
			fclose(pFileBin);
			bufferId=*contador;
			printf("El ultimo id generado fue: %d\n",bufferId);
			bufferId++;
			printf("El nuevo id generado es: %d\n",bufferId);
			contador=&bufferId;
			estado=bufferId;
		}else
			puts("No se ha podido abrir el archivo");

	pFileBin=fopen("UltimoId.bin","w");
	if(pFileBin!=NULL)
		{
			fwrite(contador,sizeof(int),1,pFileBin);
			fclose(pFileBin);
		}else
			puts("No se ha podido inizilizar el archivo");
	return estado;
}
//=======================================================================================

/*
 * brief permite selecionar un emplye por id o nombre
 * brief imprime el menu y pide opcio
 * param *pArrayListEmployee a LinkedList
 * return posicion dle empleado en la linked lis si lo logro y -1 si salio mal
 */
int employee_findPositionBy(LinkedList* pArrayListEmployee)
{
  int retorno=-1;
  int opcion;
  int id;
  char nombre[128];
  int posicion;
  if(pArrayListEmployee!=NULL)
  		{
  		opcion=menuSeleccion();
  		switch(opcion)
  			{

  				case 1://Id
  				   pedirInt(&id,"Ingres Id de empleado","Ingres Id valido",MINIMO,10000000,INTENTOS);
  				   posicion=employee_findById(pArrayListEmployee,id);
  				   break;
  			   case 2://Nombre
  				   pedirNombre(nombre,sizeof(nombre),"Ingres Nombre de emmpleado","Nombre invalido",INTENTOS);
  				   posicion=employee_findByName(pArrayListEmployee, nombre);
  				break;
  			 }
  		retorno=posicion;
  		  		}
return retorno;
}
int employee_remove(LinkedList* pArrayListEmployee)
{
	int posicion;
	int retorno;
	if(pArrayListEmployee!=NULL)
		{
		posicion=employee_findPositionBy(pArrayListEmployee);
		if(posicion>=0)
			{

			free(ll_get(pArrayListEmployee,posicion));
			ll_remove(pArrayListEmployee,posicion);
			retorno=0;
			printf("Ha sido dada de baja el empleado en posicin %d\n",posicion);
			}
		}
return retorno;
}


