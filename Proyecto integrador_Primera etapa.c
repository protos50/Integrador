//Etapa 1
#include <stdio.h>
#include <string.h>
#include <time.h>
#define longChar 100
#define midChar 35
#define cantComidas 5
#define cantBebidas 3
#define MAX 5

//Declaración de prototipos de funciones
	//Pantalla de inicio
void esperarIntro();
void firstScreen(); 
void mostrarFechaYHora(); 
void mensajeBienvenida(); 
void mensaje();
void countdownTimer();
	//Menú
void menu();
	//Ingreso de datos
void ingresarDatosClientes();
void ingresarPedidoBebida();
void ingresarPedidoComida(); 
void ingresarIdCliente();
void mostrarOpcionesComidas();
void mostrarOpcionesBebidas();
void inicializarVectoresPedidos();
char caracterRespuesta();
void mostrarPedidoCliente ();

	//Grabado de registros en archivo
void generarBinario();
void grabarPedido();
void cerrarArchivo();
void ingresarPedido();
void ingresarRta();
	//apertura de archivo para mostrar pedidos grabados
void abrirArchivoLectura ();
void mostrarPedidosGrabados();
void leerRegistro (); 
void mostrarPedidoClienteDeArchivo ();

//Tipos de datos personalizados
typedef struct /* estructura de lo que pide un cliente y su correspondiente costo */
{
	int idCliente;
	int pedidoComida [5];
	int pedidoBebida [3];
	float totalCuenta;
} tPedidoCliente;

typedef char tString[midChar];
typedef char tLongString[longChar];
typedef tString tOpcionComidas[cantComidas];
typedef tString tOpcionBebidas[cantBebidas];

//Declaración de variables globales
tPedidoCliente vr_PedidoCliente;
FILE * f_RegistrosClientes;    


tOpcionComidas opcionComidas = {"Hamburguesa[0]", "Papas[1]", "Ensalada[2]", "Pancho[3]", "Veganos[4]"}; /* opciones de comidas que el cliente elige */
tOpcionBebidas opcionBebidas = {"Agua[0]", "Gaseosa[1]", "Cerveza[2]"};									 /* opciones de bebidas que el cliente elige */
float preciosComidas[5] = {400, 130, 150, 200, 1000};													 /* arrays con precios de las comidas y bebidas */
float preciosBebidas[3] = {70, 120, 180};

int opElegidoComida;
int opElegidoBebida;

//Bloque principal
int main(){
	firstScreen();
	menu();
	countdownTimer();
    return 0;
}

/* Se abre un archivo nuevo y se asigna a la variable archivo */
void generarBinario(){
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "wb");
	printf("\nSe creo el archivo del consumo de los clientes con sus gastos!");
}

void ingresarPedido(){
	char grabar = ' ', seguirCargando = 's';
    while (seguirCargando == 's' || seguirCargando == 'S' ) {
	   ingresarDatosClientes();
	   printf ("\n\n\tDesea grabar el pedido? S = si | N = no  ");
	   grabar = caracterRespuesta ();
	   if (grabar == 's' || grabar == 'S') {
	   		grabarPedido();
	   }
	   printf ( "\n\nEscriba 'S' para continuar con el ingreso de pedidos... ");
	   seguirCargando = caracterRespuesta();
	}
}

void grabarPedido() {
	// se grabara en el archivo un registro correspondiente al cliente 
	fwrite(&vr_PedidoCliente, sizeof(tPedidoCliente), 1, f_RegistrosClientes);
	printf("\n\n\tRegistro de los pedidos del cliente insertado! ");
}

void cerrarArchivo(){
	fclose(f_RegistrosClientes); // se cierra el archivo
	printf("\n\n\tSe ha cerrado el archivo! ");
}

void firstScreen() {
	/* Generar screen de inicio del software */
	puts("\n\n\n\n");
	mensajeBienvenida();
	mostrarFechaYHora();
	fflush(stdin);
	getchar();
	system("cls");
}

void mensajeBienvenida() {
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

void mostrarFechaYHora() {
	/* Obtener y Mostrar Fecha y hora local del sistema */
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	printf("\n\n\n\n\t\t\t\t\t%s", asctime(tm));
}

void esperarIntro(){
	/* para continuar espera que el usuario ingrese enter */
	fflush(stdin);
	puts("\n\n\t\t\t   Pulsar Intro para continuar...");
	getchar();
}

void countdownTimer(){
	int i;
	system("cls");
	puts("Gracias por utilizar ->FOOD NOTIFIER<-");
	puts("\nSoftware desarrollado por: \n\t\t\t  -Pedelhez, Matias \n\t\t\t  -Soto, Micaela \n\t\t\t  -X, Gabriela \n\t\t\t  -Zini, Franco Joaquin");
	printf("\nEl programa ->FOOD NOTIFIER<- se cerrara en:  10...");
	Sleep(1000);
	for (i = 9; i > 0; i--)
	{
		if (i == 1)
		{
			printf("%d", i);
			Sleep(1000);
		}
		else
		{
			printf("%d...", i);
			Sleep(1000);
		}
	}
}

char caracterRespuesta(){
	char centinela;
	fflush(stdin);
	scanf("%c", &centinela);
	return centinela;
}

void inicializarVectoresPedidos(){
	int i;
	for (i = 0; i < cantComidas; i++)
	{
		vr_PedidoCliente.pedidoComida[i] = 0;
	}
	for (i = 0; i < cantBebidas; i++)
	{
		vr_PedidoCliente.pedidoBebida[i] = 0;
	}
}

void ingresarDatosClientes(){
	ingresarIdCliente();
	ingresarPedidoComida();
	ingresarPedidoBebida();
	system("cls");
	mostrarPedidoCliente();
}

void ingresarIdCliente(void)
{
	int idCliente;
	printf("\nIngrese id del cliente: ");
	scanf("%d", &idCliente);
	vr_PedidoCliente.idCliente = idCliente;
}

void ingresarPedidoComida() {
	system("cls");
	char respuesta = 'S';
	while (respuesta != 'N' && respuesta != 'n')
	{
		puts("\nPor favor ingrese la opcion de comida que el cliente solicito: \n");
		mostrarOpcionesComidas();
		int opElegido;
		printf("\n\n\tOpcion: ");
		scanf("%d", &opElegido);
		/* alternativa multiple que aumenta el contador de una celda del array dependiendo de que pidio el cliente para comer.  */
		/* asi conocemos que cosas eligio y que cantidades */
		switch (opElegido)
		{

		case 0:
			vr_PedidoCliente.pedidoComida[0]++;
			break;

		case 1:
			vr_PedidoCliente.pedidoComida[1]++;
			break;

		case 2:
			vr_PedidoCliente.pedidoComida[2]++;
			break;

		case 3:
			vr_PedidoCliente.pedidoComida[3]++;
			break;

		case 4:
			vr_PedidoCliente.pedidoComida[4]++;
			break;
		}
		/* condicion para continuar cargando pedidos del cliente */
		printf("\n\n\tDesea ingresar otro pedido para comer del cliente? S = si | N = no  ");
		respuesta = caracterRespuesta();
	}
}

void ingresarPedidoBebida() {
	system("cls");
	char respuesta = 'S';
	while (respuesta != 'N' && respuesta != 'n')
	{
		puts("\nPor favor ingrese la opcion de bebida que el cliente solicito: \n");
		mostrarOpcionesBebidas();
		int opElegido;
		printf("\n\n\tOpcion: ");
		scanf("%d", &opElegido);
		/* alternativa multiple que aumenta el contador de una celda del array dependiendo de que pidio el cliente para comer.  */
		/* asi conocemos que cosas eligio y que cantidades */
		switch (opElegido)
		{

		case 0:
			vr_PedidoCliente.pedidoBebida[0]++;
			break;

		case 1:
			vr_PedidoCliente.pedidoBebida[1]++;
			break;

		case 2:
			vr_PedidoCliente.pedidoBebida[2]++;
			break;
		}
		/* condicion para continuar cargando pedidos del cliente */
		printf("\n\n\tDesea ingresar otro pedido para beber del cliente? S = si | N = no  ");
		respuesta = caracterRespuesta();
	}
}
/* calcula el total que gasto el cliente en sus pedidos y lo acumula en cuentaTotal */
float calcularCuentaTotal() {
	int i;
	float total = 0;
	for (i = 0; i < cantComidas; i++)
	{
		total = total + (vr_PedidoCliente.pedidoComida[i]) * (preciosComidas[i]);
	}

	for (i = 0; i < cantBebidas; i++)
	{
		total = total + (vr_PedidoCliente.pedidoBebida[i]) * (preciosBebidas[i]);
	}

	vr_PedidoCliente.totalCuenta = total;

	return total;
}

/* muestra los dos vectores correspondientes al pedido de comida y bebida respectivamente*/
void mostrarPedidoCliente() {
	int i;
	puts("\nDatos del cliente:");
	printf("ID del cliente: %d", vr_PedidoCliente.idCliente);
	puts("\n\nComidas Pedidas:");
	for (i = 0; i < cantComidas; i++)
	{
		printf("\n%s:\t %d", opcionComidas[i], vr_PedidoCliente.pedidoComida[i]);
	}
	puts("\n\n\nBebidas Pedidas:");
	for (i = 0; i < cantBebidas; i++)
	{
		printf("\n%s:\t %d", opcionBebidas[i], vr_PedidoCliente.pedidoBebida[i]);
	}
	puts("\n----------------------------------");
	printf("Cuenta total del cliente: $%.2f", calcularCuentaTotal());
}

void mostrarPedidoClienteDeArchivo () {
	int i;
	puts("\n\nDatos del cliente:");
	printf("ID del cliente: %d", vr_PedidoCliente.idCliente);
	puts("\n\nComidas Pedidas:");
	for (i = 0; i < cantComidas; i++)
	{
		printf("\n%s:\t %d", opcionComidas[i], vr_PedidoCliente.pedidoComida[i]);
	}
	puts("\n\n\nBebidas Pedidas:");
	for (i = 0; i < cantBebidas; i++)
	{
		printf("\n%s:\t %d", opcionBebidas[i], vr_PedidoCliente.pedidoBebida[i]);
	}
	puts("\n----------------------------------");
	printf("Cuenta total del cliente: $%.2f", vr_PedidoCliente.totalCuenta);
}

void mostrarOpcionesComidas(){
	int j;
	for (j = 0; j < cantComidas; j++)
	{
		printf(" |   %s   |", opcionComidas[j]);
	}
}

void mostrarOpcionesBebidas(){
	int j;
	for (j = 0; j < cantBebidas; j++)
	{
		printf(" |   %s   |", opcionBebidas[j]);
	}
}

void abrirArchivoLectura () {
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "rb");
}

void mostrarPedidosGrabados() {
	leerRegistro ();
	while (!feof (f_RegistrosClientes)) {
		mostrarPedidoClienteDeArchivo();
		leerRegistro ();
	}
} 

void leerRegistro () {
	fread (&vr_PedidoCliente, sizeof (tPedidoCliente), 1, f_RegistrosClientes);
}
	
void menu(){
	system("cls");
	int opcion;
	inicializarVectoresPedidos();
	printf ("\n\t\t\t               *** Opciones disponibles ***\n");
	printf ("\n\t\t\t|<| (1) - Crear archivo                               |>|");
	printf ("\n\t\t\t|<| (2) - Ingresar pedidos y guardar comprobantes     |>|");
	printf ("\n\t\t\t|<| (3) - Finalizar carga                             |>|");
	printf ("\n\t\t\t|<| (4) - Ver pedidos grabados                        |>|");
	printf ("\n\t\t\t|<| (5) - Salir                                       |>|");
	printf("\n\nOpcion: ");
	scanf("%d", &opcion);
	switch (opcion) 
	{
	case 1: 
		system("cls");
		generarBinario ();
		printf("\n");
		system ("pause");
		getchar();
		menu();
		break;
	case 2: 
		system("cls");
		ingresarPedido();
		menu();
		break;
	case 3: 
		system("cls");
		cerrarArchivo(); 
		system ("pause");
		menu();
		printf("\n");
		break;
	case 4: 
		system("cls");
		abrirArchivoLectura ();
		mostrarPedidosGrabados(); 
		system ("pause");
		cerrarArchivo();
		menu();
		printf("\n");
		break;
	case 5: 
		system("cls"); 
		esperarIntro();
		printf("\n");
		break;
	default: /* vuelve a solicitar al usuario que ingrese una opcion del menu */
		fflush(stdin);
		printf("\n\nUsted ingreso una opcion no valida. Intentelo nuevamente");
		Sleep(2000);
		menu();
		break;
	}
}
