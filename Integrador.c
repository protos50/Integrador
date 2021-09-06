/* Proyecto Integrador - 1ra. Etapa */
#include <stdio.h>
#include <string.h>

#define maxChar 100

void esperarIntro(void), mensajeBienvenida(void), mensaje(void);

typedef char tString[maxChar];

int main(void)
{
	mensajeBienvenida();
	esperarIntro();
	return 0;
}

void mensajeBienvenida(void)
{
	int i = 0;
	tString msgEntrada = "\t\t\t\tBienvenidos al sistema \n\n\t\t\t\t   'FOOD NOTIFIER'";
	for (i = 0; i < strlen(msgEntrada); i++)
	{
		printf("%c", msgEntrada[i]);
		Sleep(50);
	}
}

void esperarIntro(void)
{
	fflush(stdin);
	puts("\n\nPulsar Intro para continuar...");
	getchar();
}
