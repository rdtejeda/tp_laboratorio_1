/*
 * utn.h
 *
 *  Created on: 20 sep. 2021
 *      Author: usuario
 */

#ifndef UTN_H_
#define UTN_H_

int imprimirMenu();
int pedirNumeroIntconMaxyMin(int* px, int min, int max, int intentos, char* txt, char* txtError);
int pedirNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, int reintentos);
int sumaFloat(float* z, float x, float y);
int restaFloat(float* z, float x, float y);
int multiplicacionFloat(float* z, float x, float y);
int dividirFloat(float* z, float x,float y);
int factorial(int* result, int valor);

#endif /* UTN_H_ */
