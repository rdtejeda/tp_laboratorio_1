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
#define MAXIMOID 999

/**
* \brief reserva de forma dinamica memoria para un dato tipo Employee
* \param es void
* \return Retorna *pEmployee a direcion de memoria reservada
*/
Employee* employee_new()
{
	Employee* pEmployee=(Employee*)malloc(sizeof(Employee));
	if(pEmployee==NULL)
		{
			puts("No se ha podido reservar espacio en memoria");
		}

return pEmployee;
}
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
		if(employee_setIdChar(pEmployee,idStr)!=0 ||employee_setSueldoChar(pEmployee,sueldoStr)!=0 ||
		employee_setHorasTrabajadasChar(pEmployee,horasTrabajadasStr)!=0 || employee_setNombre(pEmployee,nombreStr)!=0)
		{
			employee_delete(pEmployee);
			pEmployee=NULL;
			puts("Algun dato no ha sido valido - Intentelo nuevamente");
		}
	}else
			puts("No se ha podido crear nuevo empleado");
return pEmployee;
}
/**
* \brief libera memoria reservada de forma dinamica que no pudo ser utilizada
* \param *pEmployee
* \return es void
*/
void employee_delete(Employee* pEmployee)
{
	if(pEmployee!=NULL)
	{
		free(pEmployee);
	}
}
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Id
* \param es recibe *pLinkedListEmpleados e id buscado
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_findById(LinkedList* pLinkedListEmpleados, int id)
{
	int retorno=-1;
	int posicion;
	int largoLista;
	Employee* pAuxiliarEmployee;
	if(pLinkedListEmpleados!=NULL && id>0)
		{
		largoLista=ll_len(pLinkedListEmpleados);
		for (int i = 0; i < largoLista; i++)
			{
				pAuxiliarEmployee=ll_get(pLinkedListEmpleados, i);
				if(pAuxiliarEmployee->id==id)
				{
					if(pAuxiliarEmployee!=NULL)
					{
						posicion=i;
						break;
					}
				}
			}
		retorno=posicion;
		}
return retorno;
}
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Id
* \param es recibe *pLinkedListEmpleados e id buscado
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_modify(LinkedList* pLinkedListEmpleados)
{
	int retorno=-1;
	int posicion;
	int opcion;
	char bufferNombre[128];
	int bufferHorasTrabajadas;
	int bufferSueldo;
		if(pLinkedListEmpleados!=NULL)
			{
			posicion=employee_findPositionBy(pLinkedListEmpleados);
			if(posicion>=0 && ll_get(pLinkedListEmpleados,posicion)!=NULL)
				{
				puts("El empleado selecionado es");
				controller_ListOneEmployee(pLinkedListEmpleados, posicion);
				do
					{
					opcion=menuOpcion();
					switch(opcion)
						{
						case 1:
							pedirNombre(bufferNombre, sizeof(bufferNombre),"Ingres nuevo nombre","Nombre invalido", INTENTOS);
							employee_setNombre(ll_get(pLinkedListEmpleados, posicion),bufferNombre);
							puts("Su modificacion es");
							controller_ListOneEmployee(pLinkedListEmpleados, posicion);
							break;
						case 2:
							pedirInt(&bufferHorasTrabajadas,"Ingres Horas Trabajadas","Error ingrese entre 1 y 200",MINIMO,MAXIMOHORAS,INTENTOS);
							employee_setHorasTrabajadas(ll_get(pLinkedListEmpleados, posicion),bufferHorasTrabajadas);
							puts("Su modificacion es");
							controller_ListOneEmployee(pLinkedListEmpleados, posicion);
							break;
						case 3:
							pedirInt(&bufferSueldo,"Ingres Sueldo","Error ingrese monto valido",MINIMO,MAXIMOSUELDO,INTENTOS);
							employee_setSueldo(ll_get(pLinkedListEmpleados, posicion),bufferSueldo);
							puts("Su modificacion es");
							controller_ListOneEmployee(pLinkedListEmpleados, posicion);
							break;
						}
					}while(opcion!=4);
				retorno=0;
				}else
					puts("El empleado no fue encotrado");
			}
return retorno;
}
/**
* \brief Busca posicion en LnkedList de un Epliyee por su Nombre de empleado
* \param es recibe *pLinkedListEmpleados e array de char name
* \return Retorna posicion si lo encontro y -1 si no existe Employee
*/
int employee_findByName(LinkedList* pLinkedListEmpleados, char name[])
{
	int retorno=-1;
	int posicion;
	int largoLista;
	Employee* pAuxiliarEmployee;
	if(pLinkedListEmpleados!=NULL && name!=NULL)
		{
		largoLista=ll_len(pLinkedListEmpleados);
		for (int i = 0; i < largoLista; i++)
			{
				pAuxiliarEmployee=ll_get(pLinkedListEmpleados, i);
				if(!strcmp(pAuxiliarEmployee->nombre,name))
				{
					posicion=i;
					retorno=posicion;
					break;
				}
			}
		}
return retorno;
}
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
/**
* \brief setea valor de nombre en una entidad *Employee
* \param *pEmployee y *nombre char
* \return 0 si lo logro y -1 todo mal
*/
int employee_setNombre(Employee* this,char* nombre)
{
int retorno=-1;
if(this!=NULL && nombre!=NULL && esNombre(nombre)==0)
	{
	strncpy(this->nombre,nombre,sizeof(this->nombre));
	retorno=0;
	}
return retorno;
}
/**
* \brief entrega el valor de nombre deuna entidad *Employee
* \param *pEmployee y *nombre chart
* \return 0 si lo logro y -1 todo mal
*/
int employee_getNombre(Employee* this,char* nombre)
{
int retorno=-1;
if(this!=NULL && nombre!=NULL )
{

	strcpy(nombre,this->nombre);
	retorno=0;
}
return retorno;
}
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
/**
  * \brief me da un id consecutivo y no repetido memorizando el ultimolvalor
  * \param void
  * \return Retorna nuevo id si todo bien  y -1 si no logro
  */
int dameUnIdNuevoEmployee(void)
{
	//TEMPORAL se Ejcutó una sola vez al principio
	/*
	int id=MAXIMOID;
	int cantidadt;
	FILE* pFileBinTemp;
	pFileBinTemp=fopen("UltimoId.bin","w");
	if(pFileBinTemp!=NULL)
		{
			cantidadt=fwrite(&id,sizeof(int),1,pFileBinTemp);
			printf("Cantidad de fwrite dice %d\n",cantidadt);
			fclose(pFileBinTemp);
		}else
				 puts("No se ha podido inizilizar el archivo");
	*/
	//TEMPORAL
	int estado=-1;
	int contador;
	FILE* pFileBin;
	pFileBin=fopen("UltimoId.bin","r");
	if(pFileBin!=NULL)
		{
			fread(&contador,sizeof(int),1,pFileBin);
			fclose(pFileBin);
			printf("El ultimo id generado fue: %d\n",contador);
			contador++;
			printf("El nuevo id generado es: %d\n",contador);
			estado=contador;
		}else
			puts("No se ha podido abrir el archivo");

	pFileBin=fopen("UltimoId.bin","w");
	if(pFileBin!=NULL)
		{
			fwrite(&contador,sizeof(int),1,pFileBin);
			fclose(pFileBin);
		}else
			puts("No se ha podido inizilizar el archivo");
	return estado;
}
/**
  * \brief me da el id mas grande
  * \param void
  * \return Retorna mayor id si todo bien  y -1 si no lo logro
  */
int employee_dameMayorID(void)
{
	int mayorId=-1;
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
		contador=&bufferId;
		mayorId=bufferId;
			}else
				puts("No se ha podido abrir el archivo");
return mayorId;
}
/*
 * brief permite selecionar un employe por id o nombre
 * brief imprime el menu y pide opcio
 * param *pLinkedListEmpleados a LinkedList
 * return posicion dle empleado en la linked lis si lo logro y -1 si salio mal
 */
int employee_findPositionBy(LinkedList* pLinkedListEmpleados)
{
  int retorno=-1;
  int opcion;
  int id;
  char nombre[128];
  int posicion;
  if(pLinkedListEmpleados!=NULL)
  		{
	  	  controller_ListEmployee(pLinkedListEmpleados);
	  	  opcion=menuSeleccion();
	  	  switch(opcion)
				{
					case 1:
					   pedirInt(&id,"Ingres Id de empleado","Ingres Id valido",MINIMO,employee_dameMayorID(),INTENTOS);
					   posicion=employee_findById(pLinkedListEmpleados,id);
					   break;
					case 2:
					   pedirNombre(nombre,sizeof(nombre),"Ingres Nombre de emmpleado","Nombre invalido",INTENTOS);
					   posicion=employee_findByName(pLinkedListEmpleados, nombre);
					break;
				 }
	  	  retorno=posicion;
  		 }
return retorno;
}
/*
 * brief permite eliminar un employee lo elige, busca posición
 * param *pLinkedListEmpleados a LinkedList
 * return o si todo bien y -1 si salio mal
 */
int employee_remove(LinkedList* pLinkedListEmpleados)
{
	int posicion;
	int retorno;
	if(pLinkedListEmpleados!=NULL)
		{
		posicion=employee_findPositionBy(pLinkedListEmpleados);
		if(posicion>=0 && ll_get(pLinkedListEmpleados,posicion)!=NULL )
			{
			puts("Se ha dado de baja al empleado");
			controller_ListOneEmployee(pLinkedListEmpleados,posicion);
			free(ll_get(pLinkedListEmpleados,posicion));
			ll_remove(pLinkedListEmpleados,posicion);
			retorno=0;
			}else
				puts("El empleado no fue encotrado");
		}
return retorno;
}
/*
 * brief transfiere los valores de sueldo de dos entidades employee
 * brief recibe dos punteros *void
 * return 1 o -1 segun el criterio establecido
 */
int employee_Criterio_ShortBySueldo(void* pVoidUno, void* pVoidCero)
{
	int retorno=0;
	Employee* pEmployeeCero;
	Employee* pEmployeeUno;

	pEmployeeCero=(Employee*)pVoidCero;
	pEmployeeUno=(Employee*)pVoidUno;


	if(pEmployeeCero->sueldo<pEmployeeUno->sueldo)
		{
			retorno=1;
		}
	if(pEmployeeCero->sueldo>pEmployeeUno->sueldo)
		{
			retorno=-1;
		}
return retorno;
}
/*
 * brief  transfiere los valores de horas trabajadas de dos entidades employee
 * brief recibe dos punteros *void
 * return 1 o -1 segun el criterio establecido
 */
int employee_Criterio_ShortByHoras(void* pVoidUno, void* pVoidCero)
{
	int retorno=0;
	Employee* pEmployeeCero;
	Employee* pEmployeeUno;

	pEmployeeCero=(Employee*)pVoidCero;
	pEmployeeUno=(Employee*)pVoidUno;


	if(pEmployeeCero->horasTrabajadas<pEmployeeUno->horasTrabajadas)
		{
			retorno=1;
		}
	if(pEmployeeCero->horasTrabajadas>pEmployeeUno->horasTrabajadas)
		{
			retorno=-1;
		}
return retorno;
}
/*
 * brief  transfiere los valores de idde dos entidades employee
 * brief recibe dos punteros *void
 * return 1 o -1 segun el criterio establecido
 */
int employee_Criterio_ShortByID(void* pVoidUno, void* pVoidCero)
{
	int retorno=0;
	Employee* pEmployeeCero;
	Employee* pEmployeeUno;

	pEmployeeCero=(Employee*)pVoidCero;
	pEmployeeUno=(Employee*)pVoidUno;

	if(pEmployeeCero->id<pEmployeeUno->id)
		{
			retorno=1;
		}
	if(pEmployeeCero->id>pEmployeeUno->id)
		{
			retorno=-1;
		}
return retorno;
}
/*
 * brief  transfiere los valores de nombre dos entidades employee
 * brief recibe dos punteros *void
 * return 1 o -1 segun el criterio establecido
 */
int employee_Criterio_ShortByName(void* pVoidUno, void* pVoidCero)
{
	int retorno=0;
	char namecero[128];
	char nameuno[128];

	Employee* pEmployeeCero;
	Employee* pEmployeeUno;

	pEmployeeCero=(Employee*)pVoidCero;
	pEmployeeUno=(Employee*)pVoidUno;

	strncpy(namecero,pEmployeeCero->nombre,sizeof(namecero));
	strncpy(nameuno,pEmployeeUno->nombre,sizeof(nameuno));

	if(strcmp(namecero,nameuno)<0)
		{
			retorno=1;
		}
	if(strcmp(namecero,nameuno)>0)
		{
			retorno=-1;
		}
return retorno;
}
