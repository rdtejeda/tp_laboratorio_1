int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);
//int controller_findPositionBy(LinkedList* pArrayListEmployee);
int controller_shotdown(LinkedList* listaEmpleados,int estadoBin,int estadoCsv);
int controller_ListOneEmployee(LinkedList* pArrayListEmployee, int posicion);

int employee_Criterio_Short(LinkedList* pEployeeCero, LinkedList* pEplyeeUno);
