/* Proyecto Integrador - 3ra. Etapa */
/* rama estapa-3 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define longChar 100
#define midChar 35
#define cantComidas 5
#define cantBebidas 3
#define MAX 5

typedef char tString[midChar];
typedef char tLongString[longChar];
typedef tString tOpcionComidas[cantComidas];
typedef tString tOpcionBebidas[cantBebidas];

typedef struct /* estructura de lo que pide un cliente y su correspondiente costo */
{
	int idCliente;
	int pedidoComida[5];
	int pedidoBebida[3];
	float totalCuenta;
} tPedidoCliente;

tPedidoCliente vr_PedidoCliente;

typedef struct nodo
{
	tPedidoCliente datosPedidos;
	struct nodo *siguiente;
} tNodo;

typedef struct
{
	tNodo *principio;
	tNodo *final;
} tCola;

tCola colaPedidos;

void esperarIntro(void), firstScreen(void), mostrarFechaYHora(void), mensajeBienvenida(void), mensaje(void);
void generarBinario(void), ingresarDatosClientes(void), mostrarOpcionesComidas(void), mostrarOpcionesBebidas(void);
void mostrarPedidoCliente(void), mostrarPedidoCliente(void), finalizarGrabadoRegistros(void), CountdownTimer(void);
void grabarArchivoConsumoClientes(tCola), grabarRegistros(tNodo *), inicializarCola(void), Menu(void);
void ingresarPedidoBebida(void), ingresarPedidoComida(void), ingresarIdCliente(void);
void agregarElemento(tPedidoCliente), inicializarVectores(void), visualizarElementos(tCola);
void removerElemento(void), eliminarProductoPosicionN(int), removerPrimerElemento(void);
void iniciarProcesoLectura(void), procesarPedidosClientes(void), finalizarProcesoLectura(void), obtenerCliente(void);
void procesarPedido(void);
void inicializacionCorte(void), procesoCorte(void), unPedido(int *, float *);

bool colaVacia(tCola);
bool seEncuentraCliente(int);
int cantidadNodos(void);
float calcularCuentaTotal(void);
char caracterRespuesta(void);

FILE *f_RegistrosClientes;

tOpcionComidas opcionComidas = {"Hamburguesa[0]", "Papas[1]", "Ensalada[2]", "Pancho[3]", "Veganos[4]"}; /* opciones de comidas que el cliente elige */
tOpcionBebidas opcionBebidas = {"Agua[0]", "Gaseosa[1]", "Cerveza[2]"};									 /* opciones de bebidas que el cliente elige */
float preciosComidas[5] = {400, 130, 150, 200, 1000};													 /* arrays con precios de las comidas y bebidas */
float preciosBebidas[3] = {70, 120, 180};
float sumTotalVentas = 0;

int opElegidoComida;
int opElegidoBebida;
int controlIniciacion = 0;
int cantPedidosRegistrados = 0;
int posClienteBuscado;
int totalPedidos = 0;

int main(void)
{
	// firstScreen();
	Menu();
	CountdownTimer();
	return 0;
}

void inicializarCola(void)
{
	if (controlIniciacion == 0)
	{
		colaPedidos.principio = NULL;
		colaPedidos.final = NULL;
		printf("Se inicializo la cola de pedidos ... \n");
		esperarIntro();
		controlIniciacion++;
	}
	else
	{
		puts("\nUsted ya inicializo la cola previamente! Ya puede agregar pedidos a la cola");
		esperarIntro();
	}
}

bool colaVacia(tCola pCola)
{
	return (pCola.principio == NULL && pCola.final == NULL);
}

void agregarElemento(tPedidoCliente pPedidoCliente)
{
	tNodo *nuevoNodo;

	nuevoNodo = (tNodo *)malloc(sizeof(tNodo));

	nuevoNodo->datosPedidos = pPedidoCliente;

	nuevoNodo->siguiente = NULL;

	if (colaVacia(colaPedidos))
	{
		// estamos insertando el primer nodo
		colaPedidos.principio = nuevoNodo;
		colaPedidos.final = nuevoNodo;
	}
	else
	{
		// cuando ya hay por lo menos un elemento
		colaPedidos.final->siguiente = nuevoNodo;
		colaPedidos.final = nuevoNodo;
	}

	printf("\n\n\tEl pedido del cliente ingreso a la cola!\n");

	esperarIntro();
}

void removerElemento(void)
{
	int idClientePedido;

	// Checkea si existen elementos para borrar
	if (colaVacia(colaPedidos))
	{
		printf("No hay elementos para eliminar");
	}
	else // si existe por lo menos un nodo para borrar
	{
		tNodo *nodoSuprimir;
		nodoSuprimir = colaPedidos.principio;

		// ingreso ID del cliente que se quiere eliminar de la cola
		puts("Por favor ingrese el ID del cliente que desea eliminar en la cola de los pedidos: ");
		scanf("%d", &idClientePedido);

		/* Se verifica que el ID ingresado se encuentre en algun pedido.  */
		if (!seEncuentraCliente(idClientePedido))
		{
			puts("\nNo se encontro el pedido de ese cliente. ID invalido!"); // no se encontró el ID
		}
		else // sí se encuentró el ID para borrar ese registro de pedido
		{
			// consultar si la cola es unitaria para re inicializar la cola
			if (colaPedidos.principio == colaPedidos.final)
			{
				controlIniciacion = 0;
				inicializarCola();
			}
			else // la cola tiene mas de 1 elemento y se borrara por id
			{
				eliminarProductoPosicionN(posClienteBuscado);
			}
		}
	}
}

void removerPrimerElemento(void)
{
	if (colaVacia(colaPedidos))
	{
		printf("No hay elementos para eliminar");
	}
	else // si existe por lo menos un nodo para borrar
	{
		tNodo *nodoSuprimir;
		nodoSuprimir = colaPedidos.principio;
		// re inicializar la cola
		if (colaPedidos.principio == colaPedidos.final)
		{
			controlIniciacion = 0;
			inicializarCola();
		}
		else
		{ // se borra elemento del frente de la cola
			colaPedidos.principio = nodoSuprimir->siguiente;
		}

		printf("\nSe elimino el cliente ID: %d del frente de la Cola de pedidos\n", nodoSuprimir->datosPedidos.idCliente);
		free(nodoSuprimir);
		nodoSuprimir = NULL;
	}
}

void eliminarProductoPosicionN(int pPosClienteBuscado)
{
	int i;
	tNodo *aux;
	tNodo *nodoSuprimir;

	aux = colaPedidos.principio;

	for (i = 1; i < pPosClienteBuscado - 1; i++)
	{
		aux = aux->siguiente;
	}

	nodoSuprimir = aux->siguiente;
	// verificacion si se trata del ultimo nodo de la cola
	if (cantidadNodos() == pPosClienteBuscado)
	{
		// el puntero al nodo del final de la cola apunta ahora al nodo anterior al que se eliminará
		colaPedidos.final = aux;
	}

	aux->siguiente = nodoSuprimir->siguiente; // si nodoSuprimir es el ultimo nodo entonces: aux->siguiente = NULL
	printf("\nSe elimino el cliente ID: %d de la posicion %d.\n", nodoSuprimir->datosPedidos.idCliente, pPosClienteBuscado);
	free(nodoSuprimir);
	nodoSuprimir = NULL;
}

/* recibe como parámetro el nro de cliente a eliminar y trabaja con la cola global*/
bool seEncuentraCliente(int pIdClientePedido)
{
	bool existeID = false;
	tNodo *aux;
	posClienteBuscado = 0;
	aux = colaPedidos.principio;

	// se recorre toda la cola verificando si existe un cliente con ese ID
	while (aux != NULL)
	{
		posClienteBuscado++;
		if (pIdClientePedido == aux->datosPedidos.idCliente)
		{
			// existe el cliente ID que realizo algun pedido, por lo que se retorna true.
			existeID = true;
			break;
		}
		aux = aux->siguiente;
	}
	return existeID;
}

int cantidadNodos(void)
{
	int cantidadNodos = 0;

	if (!colaVacia(colaPedidos))
	{
		tNodo *aux;
		aux = colaPedidos.principio;

		while (aux != NULL)
		{
			cantidadNodos++;
			aux = aux->siguiente;
		}
	}
	return cantidadNodos;
}

void visualizarElementos(tCola pCola)
{
	tNodo *aux;
	aux = pCola.principio;

	if (colaVacia(pCola))
	{
		printf("\nNo hay pedidos realizados\n");
		esperarIntro();
	}
	else
	{
		printf("Clientes en la cola: \n");

		while (aux != NULL)
		{
			int j;
			puts("\n----------------------------------");
			puts("\n\nDatos del cliente:");
			printf("ID del cliente: %d", aux->datosPedidos.idCliente);
			puts("\n\nComidas Pedidas:");
			// dado que pedidoComida es un vector tengo que mostrarlo con un for tambien
			for (j = 0; j < cantComidas; j++)
			{
				printf("\n%s:\t %d", opcionComidas[j], aux->datosPedidos.pedidoComida[j]);
			}
			puts("\n\n\nBebidas Pedidas:");
			for (j = 0; j < cantBebidas; j++)
			{
				printf("\n%s:\t %d", opcionBebidas[j], aux->datosPedidos.pedidoBebida[j]);
			}
			puts("\n----------------------------------");
			printf("Cuenta total del cliente: $%.2f", aux->datosPedidos.totalCuenta);

			aux = aux->siguiente;
		}

		puts("\n");
		esperarIntro();
	}
}

void inicializacionCorte(void)
{
	// mayorNota = 0;

	// abro en modo lectura el archivo .dat
	iniciarProcesoLectura();
	// lectura adelantada del primer registro del fichero
	obtenerCliente();

	printf("\n\t\t *** Listado de pedidos por intervalo de precios *** ");
	printf("\n-----------------------------------------------------\n");
	printf("  Rango precio \t|\tID \t|\t Total");
	printf("\n-----------------------------------------------------\n");
}
// (recordar)a mejorar y optimizar esta funcion de corte de control :-)
void procesoCorte(void)
{
	int cantVentasRango = 0;
	float sumVentasRango = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf(" \n$0 - $800 \n");
	while (!feof(f_RegistrosClientes))
	{
		if (vr_PedidoCliente.totalCuenta >= 0 && vr_PedidoCliente.totalCuenta <= 800)
		{
			unPedido(&cantVentasRango, &sumVentasRango);
		}
		obtenerCliente();
	}

	if (cantVentasRango == 0)
	{
		printf("\n No hay ventas registras en este rango de precio!\n");
	}
	else
	{
		printf("\n\n Cantidad de ventas entre $0 y $800: %d", cantVentasRango);
		printf("\n\n Promedio de ventas entre $0 y $800: %.2f", sumVentasRango / cantVentasRango);
	}

	fclose(f_RegistrosClientes); // se cierra el archivo
	printf("\n----------------------------------------------------------------------------------------\n");

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	iniciarProcesoLectura();
	cantVentasRango = 0;
	sumVentasRango = 0;
	printf(" \n$800 - $1600 \n");
	while (!feof(f_RegistrosClientes))
	{
		if (vr_PedidoCliente.totalCuenta > 800 && vr_PedidoCliente.totalCuenta <= 1600)
		{
			unPedido(&cantVentasRango, &sumVentasRango);
		}
		obtenerCliente();
	}

	if (cantVentasRango == 0)
	{
		printf("\n No hay ventas registras en este rango de precio!\n");
	}
	else
	{
		printf("\n\n Cantidad de ventas entre $800 y $1600: %d", cantVentasRango);
		printf("\n\n Promedio de ventas entre $800 y $1600: %.2f", sumVentasRango / cantVentasRango);
	}

	fclose(f_RegistrosClientes); // se cierra el archivo
	printf("\n----------------------------------------------------------------------------------------\n");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	iniciarProcesoLectura();
	cantVentasRango = 0;
	sumVentasRango = 0;
	printf(" \nMayor a $1600 \n");
	while (!feof(f_RegistrosClientes))
	{
		if (vr_PedidoCliente.totalCuenta >= 1600)
		{
			unPedido(&cantVentasRango, &sumVentasRango);
		}
		obtenerCliente();
	}

	if (cantVentasRango == 0)
	{
		printf("\n No hay ventas registras en este rango de precio!\n");
	}
	else
	{
		printf("\n\n Cantidad de ventas mayor a 1600: %d", cantVentasRango);
		printf("\n Promedio de ventas mayor a 1600: %.2f", sumVentasRango / cantVentasRango);
	}

	fclose(f_RegistrosClientes); // se cierra el archivo
	printf("\n----------------------------------------------------------------------------------------\n");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("\n\n----------------------------------------------------------------------------------------\n");

	printf("\n Cantidad de ventas realizadas en total: %d", totalPedidos);
	printf("\n Cantidad recaudada en total: %.2f", sumTotalVentas);
	printf("\n Promedio de ventas total: %.2f", sumTotalVentas / totalPedidos);

	printf("\n----------------------------------------------------------------------------------------\n");
}

void unPedido(int *pCantVentasRango, float *pSumVentasRango)
{
	float totalCliente = vr_PedidoCliente.totalCuenta;
	int ID = vr_PedidoCliente.idCliente;
	sumTotalVentas += totalCliente;
	totalPedidos++;
	*pSumVentasRango += totalCliente;
	*pCantVentasRango += 1;
	printf("\n\t\t\t%d \t\t %.2f", ID, totalCliente);
}

/* Se abre un archivo nuevo y se asigna a la variable archivo */
void generarBinario(void)
{
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "wb");
	printf("\nSe creo el archivo del consumo de los clientes con sus gastos!");
}
/* grabar los registros en el archivo */
void grabarArchivoConsumoClientes(tCola pCola)
{
	tNodo *aux;
	aux = pCola.principio;
	// proceso de guardar los registros de los clientes en un archivo
	while (aux != NULL)
	{
		grabarRegistros(aux);

		aux = aux->siguiente;
	}
}

void iniciarProcesoLectura(void)
{
	f_RegistrosClientes = fopen("ConsumoClientes.dat", "rb");
}

void grabarRegistros(tNodo *pAux)
{
	// se grabara en el archivo el registro correspondiente al cliente
	fwrite(&pAux->datosPedidos, sizeof(tPedidoCliente), 1, f_RegistrosClientes);
	printf("\n\n\tRegistro de los pedidos del cliente insertado! ");
}

void procesarPedidosClientes(void)
{
	obtenerCliente(); /* lectura adelantada */
	while (!feof(f_RegistrosClientes))
	{
		procesarPedido();
		obtenerCliente();
	}
}

void procesarPedido(void)
{
	mostrarPedidoCliente();
	cantPedidosRegistrados++;
}

void obtenerCliente(void)
{
	/* Se obtiene un registro de un cliente del archivo para leerlo */
	fread(&vr_PedidoCliente, sizeof(tPedidoCliente), 1, f_RegistrosClientes);
}

void finalizarGrabadoRegistros(void)
{
	fclose(f_RegistrosClientes); // se cierra el archivo
}

void finalizarProcesoLectura(void)
{
	printf("\nCantidad de pedidos registrados: %d", cantPedidosRegistrados);
	fclose(f_RegistrosClientes); // se cierra el archivo
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

void ingresarIdCliente(void)
{
	int idCliente;
	printf("\nIngrese id del cliente: ");
	scanf("%d", &idCliente);
	vr_PedidoCliente.idCliente = idCliente;
}

void ingresarPedidoComida(void)
{
	system("cls");
	printf("\nDesea ingresar un pedido que realizo un cliente para comer? S = si | N = no  ");
	char respuesta = caracterRespuesta();
	while (respuesta != 'N' && respuesta != 'n')
	{
		puts("\nPor favor ingrese la opcion que el cliente solicito: ");
		mostrarOpcionesComidas();
		int opElegido;
		printf("\nOpcion: ");
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
		printf("\nDesea ingresar un pedido para comer del cliente? S = si | N = no  ");
		respuesta = caracterRespuesta();
	}
}

void ingresarPedidoBebida(void)
{
	system("cls");
	printf("\nDesea ingresar un pedido que realizo un cliente para beber? S = si | N = no  ");
	char respuesta = caracterRespuesta();
	while (respuesta != 'N' && respuesta != 'n')
	{
		puts("\nPor favor ingrese la opcion que el cliente solicito: ");
		mostrarOpcionesBebidas();
		int opElegido;
		printf("\nOpcion: ");
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
		printf("\nDesea ingresar un pedido para beber del cliente? S = si | N = no  ");
		respuesta = caracterRespuesta();
	}
}
/* calcula el total que gasto el cliente en sus pedidos y lo acumula en cuentaTotal */
float calcularCuentaTotal(void)
{
	int i;
	float total = 0;
	for (i = 0; i < cantComidas; i++)
	{
		total += (vr_PedidoCliente.pedidoComida[i]) * (preciosComidas[i]);
	}

	for (i = 0; i < cantBebidas; i++)
	{
		total += (vr_PedidoCliente.pedidoBebida[i]) * (preciosBebidas[i]);
	}

	vr_PedidoCliente.totalCuenta = total;

	return total;
}

/* muestra los dos vectores correspondientes al pedido de comida y bebida respectivamente de cada cliente*/
void mostrarPedidoCliente(void)
{
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

void ingresarDatosClientes(void)
{
	inicializarVectores();
	ingresarIdCliente();
	ingresarPedidoComida();
	ingresarPedidoBebida();
	system("cls");
	mostrarPedidoCliente();
}

void inicializarVectores(void)
{
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

void Menu(void)
{
	system("cls");
	int opcion;
	printf("\t*** Opciones disponibles ***\n");
	printf("\t1- Iniciar Cola.  \n\t2- Agregar pedidos a la Cola. \n\t3- Visualizar pedidos en Cola. \n\t4- Eliminar cliente de la cola. \n");
	printf("\t5- Guardar comprobantes de los pedidos. \n\t6- Leer los comprobantes de los pedidos guardados. \n\t7- Corte de control. \n\t8- Salir.");
	printf("\nOpcion: ");
	scanf("%d", &opcion);
	switch (opcion)
	{
	case 1: /*  */
		system("cls");
		inicializarCola();
		Menu();
		break;
	case 2: /*  */
		system("cls");
		ingresarDatosClientes();
		agregarElemento(vr_PedidoCliente);
		Menu();
		break;
	case 3: /*  */
		system("cls");
		visualizarElementos(colaPedidos);
		Menu();
		break;
	case 4: /* Eliminar un cliente de los pedidos */
		system("cls");
		printf("Que desea hacer:\n\n*Eliminar del frente de la cola: 1\n*Eliminar por ID de cliente: Cualquier otro caracter \n\t\t\t\t\t\t    _");
		(caracterRespuesta() == '1') ? removerPrimerElemento() : removerElemento();
		esperarIntro();
		Menu();
		break;

	case 5: /* Guargar los registros de los pedidos de los clientes a un fichero */
		system("cls");
		generarBinario();
		grabarArchivoConsumoClientes(colaPedidos);
		finalizarGrabadoRegistros();
		esperarIntro();
		Menu();
		break;
	case 6: /* Leer los registros de los pedidos de los clientes desde un fichero  */
		system("cls");
		iniciarProcesoLectura();
		procesarPedidosClientes();
		finalizarProcesoLectura();
		esperarIntro();
		Menu();
		break;
	case 7: /* Finalizar Programa */
		system("cls");
		inicializacionCorte();
		procesoCorte();
		esperarIntro();
		Menu();
		break;
	case 8: /* Finalizar Programa */
		system("cls");
		printf("\n");
		break;
	default: /* el default me vuelve a pedir que ingrese una opcion de este menu */
		fflush(stdin);
		printf("\n\nUsted ingreso una opcion no valida. Intentelo nuevamente");
		Sleep(2000);
		Menu();
		break;
	}
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

char caracterRespuesta(void)
{
	char centinela;
	fflush(stdin);
	scanf("%c", &centinela);
	return centinela;
}

void esperarIntro(void)
{
	/* para continuar espera que el usuario ingrese enter */
	fflush(stdin);
	puts("\n\n\t\t\t   Pulsar Intro para continuar...");
	getchar();
}

void CountdownTimer(void)
{
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
