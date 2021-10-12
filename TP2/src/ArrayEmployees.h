/*
 * ArrayEmployees.h
 *
 *  Created on: 7 oct. 2021
 *      Author: usuario
 */

#ifndef ARRAYEMPLOYEES_H_
#define ARRAYEMPLOYEES_H_

typedef struct{
 int id;
 char name[51];
 char lastName[51];
 float salary;
 int sector;
 int isEmpty;
}eEmployee;

int initEmployees(eEmployee *plistEmployee,int len);
int printEmployees(eEmployee *plistEmployee,int len);
int addEmployee(eEmployee *plistEmployee,int len,int id,char name[],char lastName[],float salary,int sector);
int findEmployeeById(eEmployee *plistEmployee,int len,int id);
int removeEmployee(eEmployee *plistEmployee,int len,int id);
int sortEmployees(eEmployee *plistEmployee,int len,int order);

int modifyOneEmploye(eEmployee *plistEmployee, int len);
int operateSalaryEmployees(eEmployee *plistEmployee,int len,float *totalSalary, float *promSalary, int *overProm);
int listlong(eEmployee *plistEmployee,int len);
int findFreePlace(eEmployee *plistEmployee,int len);

#endif /* ARRAYEMPLOYEES_H_ */
