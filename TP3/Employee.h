#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();//RESERVA ESPACIO EN MEMORIA DINAMICA PARA UN DATO TIO EMPLOYEE "LESTO"
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);//HACE PUNTERP *EMPLYE Y SET VALORES

void employee_delete(Employee* pEmployee);

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);
int employee_getRetSueldo(Employee* this);

int employee_findByName(LinkedList* listEmployees, char name[]);
int dameUnIdNuevoEmployee(void);
int employee_modify(LinkedList* listEmployees);
int employee_findPositionBy(LinkedList* pArrayListEmployee);

int employee_setIdChar(Employee* this,char* id);//YO
int employee_getRetId(Employee* this);//YO

int employee_setHorasTrabajadasChar(Employee* this,char* horasTrabajadas);//YO
int employee_getRetHorasTrabajadas(Employee* this);//YO

int employee_setSueldoChar(Employee* this,char* sueldo);//YO

int employee_findById(LinkedList* listEmployees, int id);//YO
int employee_remove(LinkedList* pArrayListEmployee);

int employee_Criterio_ShortBySueldo(void* pVoidUno, void* pVoidCero);
int employee_Criterio_ShortByID(void* pVoidUno, void* pVoidCero);
int employee_Criterio_ShortByHoras(void* pVoidUno, void* pVoidCero);
int employee_Criterio_ShortByName(void* pVoidUno, void* pVoidCero);


#endif // employee_H_INCLUDED
