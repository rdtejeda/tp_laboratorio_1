/*
 ============================================================================
 Name        : TP_1.c
 Author      : TEJEDA Roberto Daniel
 Description : Enunciado
	Hacer una calculadora.Para ello el programa iniciará y contará con un menú de opciones:
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
• Todas las funciones matemáticas del menú se deberán realizar en una biblioteca aparte,
que contenga las funciones para realizar las cinco operaciones.
• En el menú deberán aparecer los valores actuales cargados en los operandos A y B
(donde dice “x” e “y” en el ejemplo, se debe mostrar el número cargado)
• Deberán contemplarse los casos de error (división por cero, etc)
• Documentar todas las funciones
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
	float x=0;
	float y=0;
	int valIntx;
	int valInty;
	int operadorAValido=-1;
	int operadorBValido=-1;
	int opciones;
	float resultSuma;
	float resultResta;
	float resultMultiplica;
	float resultDivision;
	int estadoDivision=-1;
	int calcular;
	int estadoFactA=-1;
	int estadoFactB=-1;
	int resultFactA;
	int resultFactB;
	printf("\nBienvenide a la calculador\n"); //SALUDO DE BIENVENIDA
	do
	{
		opciones=imprimirMenu(x, y); //IMPRIMO EL MENÚ
		switch (opciones)
		{
			case 1: //PIDO Y VALIDO OPERADOR A
				operadorAValido=pedirFloat(&x, "Ingresar 1er operando (A)", "Ingrese un NUMERO Float", INTENTOS);
				calcular=-1; //SOLICITO CALCULAR
				break;
			case 2: //PIDO Y VALIDO OPERDADOR B
				operadorBValido=pedirFloat(&y, "Ingresar 2do operando (B)", "Ingrese un NUMERO Float", INTENTOS);
				calcular=-1; //SOLICITO CALCULAR
				break;
			case 3: //CALCULO
				if(operadorAValido==0 && operadorBValido==0) //VERIFICO OPERADORES VALIDOS
				{
					sumaFloat(&resultSuma, x, y); //CALCULO
					restaFloat(&resultResta, x, y);
					multiplicacionFloat(&resultMultiplica, x, y);
					estadoDivision=dividirFloat(&resultDivision, x, y);
					if ((int)x-x==0) //VERIFICO QUE EL OPERADOR A SEA UN ENTERO
					{
						valIntx=(int)x;
						estadoFactA=factorial(&resultFactA, valIntx);
					}
					if((int)y-y==0) //VERIFICO QUE EL OPERADOR B SEA UN ENTERO
					{
						valInty=(int)y;
						estadoFactB=factorial(&resultFactB, valInty);
					}
				calcular=0; //CONFIRMO QUE SE HA CALCULADO
				printf("\nLAS OPERACIONES SE HAN REALIZADO\n");
				}else
				{
					printf("\n\nINGRESE OPERADORES A Y B VALIDOS\n\n");
				}
				break;
			case 4: //INFORMO RESULTADOS
				if(operadorAValido==0 && operadorBValido==0) //VERIFICO INGRESO DE OPERDORES VALIDOS
				{
					if(calcular==0)	//VERIFICO QUE SE HAYA CALCULADO O REINGRESADO UN OPERADOR
					{
						printf("\na) El resultado de %.2f + %.2f es: %.4f\n",x,y,resultSuma); //INFORMO SEGUN CORRESPONDA
						printf("\nb) El resultado de %.2f - %.2f es: %.4f\n",x,y,resultResta);
						if(estadoDivision==0)
							{
							printf("\nc) El resultado de %.2f / %.2f es: %.4f\n",x,y,resultDivision);
							}else
								{
								printf("\nc) No es posible dividir por cero\n");
								}
						printf("\nd) El resultado de %.2f * %.2f es: %.4f\n",x,y,resultMultiplica);
						if (estadoFactA==0)
							{
							printf("\ne) El factorial de %.2f es: %d\n",x, resultFactA);
							}else
								{
								printf("\nNo es posible calcular factorial de \nnumeros decimales o menores a cero\n");
								}
						if (estadoFactB==0)
							{
							printf("\ne) El factorial de %.2f es: %d\n",y, resultFactB);
							}else
								{
								printf("\nNo es posible calcular factorial de \nnumeros decimales o menores a cero\n");
								}
					}else
					{
						printf("\nPARA VER LOS RESULTADOS REALIZAR LAS OPERACIONES\n");
					}

				}else
				{
					printf("\n\nINGRESE OPERADORES A Y B VALIDOS\n\n");
				}

				break;
			default:
				break;
		}
	}while(opciones!=5); //VUELVO AL MENÚ PRINCIPAL
	printf("\nUSTED HA SALIDO DE LA CALCULADORA\n");//SALUDO DE DESPEDIDA
	return EXIT_SUCCESS;
}
