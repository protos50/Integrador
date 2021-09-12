/* Proyecto Integrador - 1ra. Etapa */
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

typedef struct
{
	tPedidoCliente vVectorPedidos[MAX];
	int frente;
	int final;
} tCola;

tCola totalPedidos;

void esperarIntro(void), firstScreen(void), mostrarFechaYHora(void), mensajeBienvenida(void), mensaje(void);
void generarBinario(void), ingresarDatosClientes(void), mostrarOpcionesComidas(void), mostrarOpcionesBebidas(void);
void mostrarPedidoCliente(void), mostrarPedidoCliente(void), finalizarGrabadoRegistros(void), CountdownTimer(void);
void grabarArchivoConsumoClientes(tCola), grabarRegistros(int), inicializarCola(void), Menu(void);
void ingresarPedidoBebida(void), ingresarPedidoComida(void), ingresarIdCliente(void);
void agregarElemento(void), inicializarVectores(void), visualizarElementos(tCola);
void removerElemento(tCola, int);

bool colaVacia(tCola);
bool colaLlena(tCola);
float calcularCuentaTotal(void);
char caracterRespuesta(void);

FILE *f_RegistrosClientes;

tOpcionComidas opcionComidas = {"Hamburguesa[0]", "Papas[1]", "Ensalada[2]", "Pancho[3]", "Veganos[4]"}; /* opciones de comidas que el cliente elige */
tOpcionBebidas opcionBebidas = {"Agua[0]", "Gaseosa[1]", "Cerveza[2]"};									 /* opciones de bebidas que el cliente elige */
float preciosComidas[5] = {400, 130, 150, 200, 1000};													 /* arrays con precios de las comidas y bebidas */
float preciosBebidas[3] = {70, 120, 180};

int opElegidoComida;
int opElegidoBebida;

int main(void)
{
	firstScreen();
	Menu();
	CountdownTimer();
	return 0;
}

void inicializarCola(void)
{
	totalPedidos.frente = -1;
	totalPedidos.final = -1;
	printf("Se inicializo la cola de pedidos ... \n");
	esperarIntro();
}

bool colaVacia(tCola pCola)
{
	return (pCola.frente == -1 && pCola.final == -1);
}

bool colaLlena(tCola pCola)
{
	return (pCola.final == (MAX - 1));
}

void agregarElemento()
{
	int i;
	if (colaLlena(totalPedidos))
	{
		printf("No hay lugares disponibles!\n");
	}
	else
	{
		/* Hay lugar para insertar */

		/* Actualizar el indice final */
		totalPedidos.final = totalPedidos.final + 1;

		/* Almacenar el elemento en la lista  */

		ingresarDatosClientes();
		totalPedidos.vVectorPedidos[totalPedidos.final] = vr_PedidoCliente;
		inicializarVectores();
		/* Verificar si se esta insertando el primer elemento */
		if (totalPedidos.final == 0)
		{
			/* Es el primer elemento */
			totalPedidos.frente = 0;
		}
		printf("\n\n\tEl pedido del cliente ingreso a la cola!\n");
	}
	esperarIntro();
}

void removerElemento(tCola cola, int pos)
{

    //Pedido de cliente vacio
    tPedidoCliente vPedidoVacio;

    if (colaVacia(cola))
    { //Checkea si existen elementos para borrar
        printf("No hay elementos para eliminar");
    }
    else
    {
        if (pos <= 0 || pos >= cola.final)
        { //Checkea que el numero de posicion sea válido
            printf("Posicion invalida. Elija una menor o igual a %d", cola.final);
        }
        else
        {
            if (pos == cola.final)
            { //Metodo para borrar en el caso que el elemento esté en el final
                cola.vVectorPedidos[cola.final] = vPedidoVacio;
                cola.final--;
            }
            else
            { //Metodo para borrar con índice personalizado
                int i;
                for (i = pos; i < cola.final; i++)
                { //Reemplaza cada elemento de la lista por el que está en frente
                    cola.vVectorPedidos[i] = cola.vVectorPedidos[i + 1];
                }
                cola.vVectorPedidos[cola.final] = vPedidoVacio; //El ultimo elemento siempre queda repitido, por lo que se vacía
                cola.final--; 
            }
        }
    }
}

void visualizarElementos(tCola pCola)
{
	int i;
	if (colaVacia(pCola))
	{
		printf("\nNo hay pedidos realizados\n");
		esperarIntro();
	}
	else
	{
		printf("Clientes en la cola: \n");
		for (i = pCola.frente; i <= pCola.final; i++)
		{
			int j;
			puts("\n----------------------------------");
			puts("\n\nDatos del cliente:");
			printf("ID del cliente: %d", pCola.vVectorPedidos[i].idCliente);
			puts("\n\nComidas Pedidas:");
			//dado que pedidoComida es un vector tengo que mostrarlo con un for tambien
			for (j = 0; j < cantComidas; j++)
			{
				printf("\n%s:\t %d", opcionComidas[j], pCola.vVectorPedidos[i].pedidoComida[j]);
			}
			puts("\n\n\nBebidas Pedidas:");
			for (j = 0; j < cantBebidas; j++)
			{
				printf("\n%s:\t %d", opcionBebidas[j], pCola.vVectorPedidos[i].pedidoBebida[j]);
			}
			puts("\n----------------------------------");
			printf("Cuenta total del cliente: $%.2f", pCola.vVectorPedidos[i].totalCuenta);
		}
		puts("\n");
		esperarIntro();
	}
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
	int i;
	//proceso de guardar los registros de los clientes en un archivo 
	for (i = pCola.frente; i <= pCola.final; i++)
	{
		grabarRegistros(i);
	}
}

void grabarRegistros(int I)
{
	// se grabara en el archivo el un registro correspondiente al cliente 
	fwrite(&totalPedidos.vVectorPedidos[I], sizeof(tPedidoCliente), 1, f_RegistrosClientes);
	printf("\n\n\tRegistro de los pedidos del cliente insertado! ");
}

void finalizarGrabadoRegistros(void)
{
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
	printf("\t1- Iniciar Cola.  \n\t2- Agregar pedidos a la Cola. \n\t3- Visualizar pedidos en Cola. \n\t4- Guardar comprobantes de cola de pedidos.\n");
	printf("\t5- Salir \n");
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
		agregarElemento();
		Menu();
		break;
	case 3: /*  */
		system("cls");
		visualizarElementos(totalPedidos);
		Menu();
		break;
	case 4: /*  */
		system("cls");
		/*puts("Este servicio aun esta en desarrollo. Por favor comuniquese con el centro de atencion al cliente del proveedor.\n\n\t Lo sentimos :("); */
		generarBinario();
		grabarArchivoConsumoClientes(totalPedidos);
		finalizarGrabadoRegistros(); 
		esperarIntro();
		Menu();
		break;
	case 5: /* Finalizar Programa */
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
//recibe como parámetro el nro de cliente a eliminar y trabaja con la cola global
void removerCliente( int nroCliente){
    int auxPos;
    tPedidoCliente vPedidoVacio;

    if (colaVacia(totalPedidos)) { 
        printf("No hay pedidos para eliminar");
    } else {	
        	int i;
		//recorre la cola hasta el final
	    	for (i=0; i< totalPedidos.final; i++) {
        		//en el caso en el que nroCliente coincida con el nroCliente guardado en la estructura dentro de la cola, borra la estructura
			if (nroCliente == totalPedidos.vVectorPedidos[i].idCliente){
        			totalPedidos.vVectorPedidos [i] = vPedidoVacio;
        			//guarda la posicion en la que se encuentra el elemento a eliminar, a fin de mover luego los registros
				auxPos = i;
        		}
            }
            for (i = auxPos; i < totalPedidos.final; i++){ //Reemplaza todos los lugares de la lista por el que está en frente
                    totalPedidos.vVectorPedidos[i] = totalPedidos.vVectorPedidos [i + 1];
                }
                totalPedidos.vVectorPedidos[totalPedidos.final] = vPedidoVacio; //El ultimo elemento siempre se repite, por lo que lo vaciamos
                totalPedidos.final -1 ;
            }
        
    }
