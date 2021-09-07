/* Proyecto Integrador - 1ra. Etapa */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define longChar 100
#define midChar 35
#define cantComidas 5
#define cantBebidas 3

void esperarIntro(void), firstScreen(void), mostrarFechaYHora(void), mensajeBienvenida(void), mensaje(void);
void generarBinario(void);

typedef char tString[midChar];
typedef char tLongString[longChar];
typedef int tVPedidosComida[cantComidas];
typedef int tVPedidosBebida[cantBebidas];
typedef tString tOpcionComidas[cantComidas];
typedef tString tOpcionBebidas[cantBebidas];

typedef struct
{
	tVPedidosComida pedidoComida;
	tVPedidosBebida pedidoBebida;
	float totalCuenta;
} tPedidoCliente;

tPedidoCliente vPedidoCliente;
FILE * f_RegistrosClientes;

tOpcionComidas opcionComidas = {"Hamburguesa[0]", "Papas Fritas[1]", "Ensalada[2]", "Pancho[3]", "Veganos[4]"};
tOpcionBebidas opcionBebidas = {"Agua[0]", "Gaseosa[1]", "Cerveza[2]"};

int main(void)
{
	firstScreen();

	esperarIntro();
	return 0;
}

/* mostrar las opciones que hay disponibles en bebida y comida
	int j;
for (j = 0; j < cantComidas; j++)
	{
		printf("\n%s", opcionComidas[j]);
		
	}
	for (j = 0; j < cantBebidas; j++)
	{
		printf("\n%s", opcionBebidas[j]);
	}
*/


/* Se abre un archivo nuevo y se asigna a la variable archivo */
void generarBinario(void) {
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "wb");
	printf("\nSe creo el archivo del consumo de los clientecon sus gastos!");
}


void firstScreen(void)
{
	/* Generar screen de inicio del software */
	puts("\n\n\n\n");
	mensajeBienvenida();
	mostrarFechaYHora();
	fflush(stdin);
	getchar();
	system("cls");
}

void mensajeBienvenida(void)
{
	int i = 0;
	tLongString msgEntrada = "\t\t\t\tBienvenidos al sistema \n\n\t\t\t\t   'FOOD NOTIFIER'";
	for (i = 0; i < strlen(msgEntrada); i++)
	{
		printf("%c", msgEntrada[i]);
		Sleep(50);
	}
	Sleep(100);
	puts("\n\n\n\t\t\t   Pulsar Intro para continuar...");
}

void mostrarFechaYHora(void)
{
	/* Obtener y Mostrar Fecha y hora local del sistema */
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("\n\n\n\n\t\t\t\t\t%s", asctime(tm));
}

void esperarIntro(void)
{
	/* para continuar espera que el ususario ingrese enter */
	fflush(stdin);
	puts("\n\n\t\t\t   Pulsar Intro para continuar...");
	getchar();
}
