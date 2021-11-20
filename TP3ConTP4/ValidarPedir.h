/*
 * ValidarPedir.h
 *
 *  Created on: 6 nov. 2021
 *      Author: usuario
 */

#ifndef VALIDARPEDIR_H_
#define VALIDARPEDIR_H_

int esNombre(char *cadena);

int pedirInt(int *pResultado, char *mensaje, char *mensajeError, int minimo, int maximo, int intentos);

int esNumericaInt(char *cadena);

int myGets(char *pResultado, int len);

int pedirNombre(char *pResultado, int len, char *mensaje, char *mensajeError, int intentos);

#endif /* VALIDARPEDIR_H_ */
