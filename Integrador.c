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
void generarBinario(void), ingresarDatosClientes(void), mostrarOpcionesComidas(void), mostrarOpcionesBebidas(void);
void ingresarPedidoBebida(void), ingresarPedidoComida(void), mostrarPedidoCliente(void);
;

typedef char tString[midChar];
typedef char tLongString[longChar];
typedef int tVPedidosComida[cantComidas];
typedef int tVPedidosBebida[cantBebidas];
typedef tString tOpcionComidas[cantComidas];
typedef tString tOpcionBebidas[cantBebidas];

typedef struct /* estructura de lo que pide un cliente y su correspondiente costo */
{
	tVPedidosComida pedidoComida;
	tVPedidosBebida pedidoBebida;
	float totalCuenta;
} tPedidoCliente;

tPedidoCliente vPedidoCliente;
FILE *f_RegistrosClientes;

tOpcionComidas opcionComidas = {"Hamburguesa[0]", "Papas[1]", "Ensalada[2]", "Pancho[3]", "Veganos[4]"}; /* opciones de comidas que el cliente elige */
tOpcionBebidas opcionBebidas = {"Agua[0]", "Gaseosa[1]", "Cerveza[2]"};									 /* opciones de bebidas que el cliente elige */
void mostrarPedidoCliente(void);

int main(void)
{
	firstScreen();
	ingresarDatosClientes();
	esperarIntro();
	return 0;
}

/* Se abre un archivo nuevo y se asigna a la variable archivo */
void generarBinario(void)
{
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "wb");
	printf("\nSe creo el archivo del consumo de los clientecon sus gastos!");
}
/* estos dos mostrar se puede hacer en una funcion, pasando como parametro el vector y la cantidad de sus elementos */
void mostrarOpcionesComidas(void)
{
	int j;
	for (j = 0; j < cantComidas; j++)
	{
		printf(" |   %s   |", opcionComidas[j]);
	}
}

void mostrarOpcionesBebidas(void)
{
	int j;
	for (j = 0; j < cantBebidas; j++)
	{
		printf(" |   %s   |", opcionBebidas[j]);
	}
}

void ingresarPedidoComida(void)
{
	char centinela;
	printf("\nDesea ingresar un pedido que realizo un cliente para comer? S = si | N = no  ");
	fflush(stdin);
	scanf("%c", &centinela);
	while (centinela != 'N' && centinela != 'n')
	{
		puts("\nPor favor ingrese la opcion que el cliente solicito: ");
		mostrarOpcionesComidas();
		int opElegido;
		printf("\nOpcion: ");
		scanf("%d", &opElegido);

		switch (opElegido)
		{

		case 0:
			vPedidoCliente.pedidoComida[0]++;
			break;

		case 1:
			vPedidoCliente.pedidoComida[1]++;
			break;

		case 2:
			vPedidoCliente.pedidoComida[2]++;
			break;

		case 3:
			vPedidoCliente.pedidoComida[3]++;
			break;

		case 4:
			vPedidoCliente.pedidoComida[4]++;
			break;
		}
		/* condicion para continuar cargando pedidos del cliente */
		printf("\nDesea ingresar un pedido para comer del cliente? S = si | N = no  ");
		fflush(stdin);
		scanf("%c", &centinela);
	}
}

void ingresarPedidoBebida(void)
{
	char centinela;
	printf("\nDesea ingresar un pedido que realizo un cliente para beber? S = si | N = no  ");
	fflush(stdin);
	scanf("%c", &centinela);
	while (centinela != 'N' && centinela != 'n')
	{
		puts("\nPor favor ingrese la opcion que el cliente solicito: ");
		mostrarOpcionesBebidas();
		int opElegido;
		printf("\nOpcion: ");
		scanf("%d", &opElegido);

		switch (opElegido)
		{

		case 0:
			vPedidoCliente.pedidoBebida[0]++;
			break;

		case 1:
			vPedidoCliente.pedidoBebida[1]++;
			break;

		case 2:
			vPedidoCliente.pedidoBebida[2]++;
			break;
		}
		/* condicion para continuar cargando pedidos del cliente */
		printf("\nDesea ingresar un pedido para beber del cliente? S = si | N = no");
		fflush(stdin);
		scanf("%c", &centinela);
	}
}
/* muestra los dos vectores correspondientes al pedido de comida y bebida respectivamente*/
void mostrarPedidoCliente(void)
{
	int i;
	puts("Datos del cliente:");
	puts("\n\nComidas Pedidas:");
	for (i = 0; i < cantComidas; i++)
	{
		printf("\n%s:\t %d", opcionComidas[i], vPedidoCliente.pedidoComida[i]);
	}
	puts("\n\n\nBebidas Pedidas:");
	for (i = 0; i < cantBebidas; i++)
	{
		printf("\n%s:\t %d", opcionBebidas[i], vPedidoCliente.pedidoBebida[i]);
	}
}

void ingresarDatosClientes(void)
{
	ingresarPedidoComida();
	ingresarPedidoBebida();
	/* scanf("%f", &vPedidoCliente.totalCuenta); falta funcion para ingresar y mostrar el total del gasto del cliente*/
	system("cls");
	mostrarPedidoCliente();
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
