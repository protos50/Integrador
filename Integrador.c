/* Proyecto Integrador - 1ra. Etapa */
#include <stdio.h>
#include <string.h>
#include <time.h>
#define maxChar 100

void esperarIntro(void), firstScreen(void), mostrarFechaYHora(void), mensajeBienvenida(void), mensaje(void);

typedef char tString[maxChar];

int main(void)
{
	firstScreen();
	esperarIntro();
	return 0;
}

void firstScreen(void)
{
	puts("\n\n\n\n");
	mensajeBienvenida();
	mostrarFechaYHora();
	fflush(stdin);
	getchar();
	system("cls");
}

void mensajeBienvenida(void)
{
	/* Generar screen de inicio del software */
	int i = 0;
	tString msgEntrada = "\t\t\t\tBienvenidos al sistema \n\n\t\t\t\t   'FOOD NOTIFIER'";
	for (i = 0; i < strlen(msgEntrada); i++)
	{
		printf("%c", msgEntrada[i]);
		Sleep(50);
	}	
	Sleep(100);
	puts("\n\n\n\t\t\t   Pulsar Intro para continuar...");
}

void mostrarFechaYHora(void){
	/* Obtener y Mostrar Fecha y hora local del sistema */
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("\n\n\n\n\t\t\t\t\t%s", asctime(tm));
}

void esperarIntro(void)
{
	fflush(stdin);
	puts("\n\n\t\t\t   Pulsar Intro para continuar...");
	getchar();
}
