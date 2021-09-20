/*
 ============================================================================
 Name        : tp_1.c
 Author      : TEJEDA Roberto Daniel
 Description :
 Enunciado
	Hacer una calculadora.
	Para ello el programa iniciará y contará con un menú de opciones:
	1. Ingresar 1er operando (A=x)
	2. Ingresar 2do operando (B=y)
	3. Calcular todas las operaciones
		a) Calcular la suma (A+B)
		b) Calcular la resta (A-B)
		c) Calcular la division (A/B)
		d) Calcular la multiplicacion (A*B)
		e) Calcular el factorial (A!)
	4. Informar resultados
		a) “El resultado de A+B es: r”
		b) “El resultado de A-B es: r”
		c) “El resultado de A/B es: r” o “No es posible dividir por cero”
		d) “El resultado de A*B es: r”
		e) “El factorial de A es: r1 y El factorial de B es: r2”
	5. Salir
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include "utn.h"
#define INTENTOS 3

int main(void)
{
	float x;
	float y;
	int a;
	int b;
	int operadorAValido;
	int operadorBValido;
	int opciones;
	float resultSuma;
	float resultResta;
	float resultMultiplica;
	float resultDivision;
	int estadoDivision;
	int estadoFactA;
	int estadoFactB;
	int resultFactA;
	int resultFactB;
	printf("\nBienvenide a la calculador\n");
	do
	{
		opciones=imprimirMenu();
		switch (opciones)
		{
			case 1:
				operadorAValido=pedirNumeroFloat(&x, INTENTOS, "Ingresar 1er operando (A)", "Ingrese un NUMERO");
				//printf("\nOperando A vale: %.4f\n",x);
				break;
			case 2:
				operadorBValido=pedirNumeroFloat(&y, INTENTOS, "Ingresar 1er operando (B)", "Ingrese un NUMERO");
				//printf("\nOperando B vale: %.4f\n",y);
				break;
			case 3:
				if(operadorAValido==0 && operadorBValido==0)
				{
				sumaFloat(&resultSuma, x, y);
				restaFloat(&resultResta, x, y);
				multiplicacionFloat(&resultMultiplica, x, y);
				estadoDivision=dividirFloat(&resultDivision, x, y);
				a=x; //printf("a vale  \n%d",a);
				b=y; //printf("b vale  \n%d",b);
				estadoFactA=factorial(&resultFactA, a);
				estadoFactB=factorial(&resultFactB, b);
				}
				break;
			case 4:
				printf("\nEl resultado de A+B es: %.4f\n",resultSuma);
				printf("\nEl resultado de A-B es: %.4f\n",resultResta);
				printf("\nEl resultado de A*B es: %.4f\n",resultMultiplica);
				if(estadoDivision==0)
				{
					printf("\nEl resultado de A/B es: %.4f\n",resultDivision);
				}else
					{
						printf("\nNo es posible dividir por cero\n");
					}
				if (estadoFactA==0)
				{
					printf("\nEl factorial de A es: %d\n", resultFactA);
				}else
					{
						printf("\nNo es posible calcular factorial de enteros menores a cero\n");
					}
				if (estadoFactB==0)
					{
							printf("\nEl factorial de b es: %d\n", resultFactB);
					}else
						{
							printf("\nNo es posible calcular factorial de enteros menores a cero\n");
						}
				break;
			default:
				break;
		}
	}while(opciones!=5);
	return EXIT_SUCCESS;
}
