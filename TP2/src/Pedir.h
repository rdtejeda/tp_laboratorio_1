/*
 * Pedir.h
 *
 *  Created on: 7 oct. 2021
 *      Author: usuario
 */

#ifndef PEDIR_H_
#define PEDIR_H_

void imprimirMenuInicial();
void imprimirMenuInformes();
void imprimirMenuModificar();

int loadNewEmployee(eEmployee plistEmployee[], int len);

int pedirCharAUsuario(char* pChar, int reintentos, char* txt, char* txtError);
int esAlfaumerica(char* cadena);
int pedirInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos);
int esNumericaInt(char* cadena);
int myGets(char pResultado[], int len);
int esNumericaFloat(char* cadena);
int pedirFloat(float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int intentos);
int pedirText(char* pResultado, int len, char* mensaje, char* mensajeError, int intentos);

#endif /* PEDIR_H_ */
