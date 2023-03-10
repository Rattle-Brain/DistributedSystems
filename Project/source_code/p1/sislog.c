#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

// Archivos de cabecera para manipulación de sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>

#include "cola.h"
#include "util.h"

#define CIERTO           1
#define FALSO            0

#define NUMFACILITIES   10
#define NUMLEVELS        8

// Estructura de datos para pasar los parametros a los hilos de atencion
struct param_hilo_aten{
    int num_hilo;
    int s;
};

typedef struct param_hilo_aten param_hilo_aten;

// ====================================================================
// PROTOTIPOS FUNCIONES
// ====================================================================
static void handler(int signum); // Manejador de señal SIGINT

// ====================================================================
// VARIABLES GLOBALES
// ====================================================================

// Cola para sincronizar los hilos de atencion de peticiones con los
// hilos trabajadores
Cola cola_eventos;

// Puerto en el que esperamos los mensajes
int puerto;

// Variable booleana que indica si el socket es orientado a conexión o no
unsigned char es_stream=CIERTO;

// Variable que almacena el numero de hilos de atencion de peticiones
int num_hilos_aten;

// Variable que almacena el numero de hilos trabajadores
int num_hilos_work;

// Puntero a la dirección de comienzo del array de datos de hilo
// de los hilos de atencion de peticiones
pthread_t *hilos_aten;

// Puntero a la dirección de comienzo del array de datos de hilo
// de los hilos trabajadores
pthread_t *hilos_work;

// Arrays para la traducción de nombres de niveles y de facilities
// y para obtener los nombres de los ficheros de registro
char * facilities_names[NUMFACILITIES]={
    "kern",
    "user",
    "mail",
    "daemon",
    "auth",
    "syslog",
    "lpr",
    "news",
    "uucp",
    "cron"};

char * level_names[NUMLEVELS]={
    "emerg",
    "alert",
    "crit",
    "err",
    "warning",
    "notice",
    "info",
    "debug"};

char * facilities_file_names[NUMFACILITIES]={
    "fac00.dat",
    "fac01.dat",
    "fac02.dat",
    "fac03.dat",
    "fac04.dat",
    "fac05.dat",
    "fac06.dat",
    "fac07.dat",
    "fac08.dat",
    "fac09.dat"};

// mutex de exclusion a los ficheros de registro
pthread_mutex_t mfp[NUMFACILITIES];


// Tamaño de la cola circular
int tam_cola;

// ====================================================================
// FUNCION handler de las señales recibidas por el hilo buque
// ====================================================================
static void handler(int signum)
{
    register int i;

    switch (signum){
        case SIGINT:
            // Si se recibe esta señal, hay que terminar "bien"
            // liberando todos los recursos en uso antes de finalizar
            // A RELLENAR
            |
            |
            |
            |
        default:
            pthread_exit(NULL);
    }
}

void procesa_argumentos(int argc,char *argv[])
{
    // A RELLENAR
    |
    |
    |
    |
}

// ====================================================================
// Implementación de los hilos
// ====================================================================

void *Worker(int *id)
{
    int id_worker;
    FILE *fp;
    dato_cola *evt;
    char msg[2048];
    char *fechahora;
    time_t timeraw;

    // Hacemos copia del parámetro recibido
    id_worker=*id;

    // y liberamos la memoria reservada para él
    free(id);

    // Mostramos información de depuración por pantalla
    sprintf(msg, "Comienza el Worker %d\n", id_worker);
    log_debug(msg);

    // Codigo del worker. Espera datos de la cola de sincronización,
    // genera en base a ellos la línea a escribir, y la escribe
    // en el fichero que corresponda. Mira "cola.h"
    // para recordar la estructura dato_cola que recibe de la cola
    while (1)
    {
        // A RELLENAR
        |
        |
        |
        |
    }
}

void * AtencionPeticiones (param_hilo_aten *q)
{
   int sock_dat, recibidos;
   struct sockaddr_in d_cliente;
   socklen_t l_dir=sizeof(d_cliente);
   char msg[100];
   char buffer[TAMMSG];
   char * token;
   char * loc;
   dato_cola *p;
   int s;  // Variable local para almacenar el socket que se recibe como parámetro
   int num_hilo; // Variable local para almacenar el numero de hilo que se recibe como parámetro
                 // (no usada, pero puedes usarla para imprimir mensajes de depuración)

   // Información de depuración
   sprintf(msg, "Comienza el Hilo de Atencion de Peticiones %d\n", q->num_hilo);
   log_debug(msg);

   // Hacemos copia de los parámetros recibidos
   s = q->s;
   num_hilo = q->num_hilo;

   // y liberamos la memoria reservada para el parámetro
   free(q);

   while (1) // Bucle infinito de atencion de mensajes
   {
        // Primero, se recibe el mensaje del cliente. Cómo se haga depende
        // de si el socket es orientado a conexión o no
        if (es_stream) // TCP
        {
            // Aceptar el cliente, leer su mensaje hasta recibirlo entero, y cerrar la conexión
            // A RELLENAR
            |
            |
            |
            |
        }
        else // UDP
        {
            // Recibir el mensaje del datagrama
            // A RELLENAR
            |
            |
            |
            |
        }
        // Una vez recibido el mensaje, es necesario separar sus partes,
        // guardarlos en la estructura adecuada, y poner esa estructura en la cola
        // de sincronización.
        // A RELLENAR
        |
        |
        |
        |
   }
}


// ====================================================================
// PROGRAMA PRINCIPAL
// ====================================================================

// Su misión es crear e inicializar los recursos de sincronización globales,
// lanzar todos los hilos y esperar a que finalicen

int main(int argc,char *argv[])
{
    register int i;   // Indice para bucles
    int *id;          // Para pasar el identificador a cada hilo trabajador
    int sock_pasivo;
    struct sockaddr_in d_local;
    param_hilo_aten *q;

    procesa_argumentos(argc,argv);

    setbuf(stdout,NULL); // quitamos el buffer de la salida estandar
    signal(SIGINT, handler); // establecemos el comportamiento ante la llegada asíncrona de la señal

    // Datos para asignar puerto al socket
    d_local.sin_family= AF_INET;
    d_local.sin_addr.s_addr=htonl(INADDR_ANY);
    d_local.sin_port=htons(puerto);

    if (es_stream) // Preparar socket TCP
    {
        // A RELLENAR
        |
        |
        |
        |
    }
    else // Preparar socket UDP
    {
        // A RELLENAR
        |
        |
        |
        |
    }

    // Asignamos el puerto al socket
    // A RELLENAR
    |
    |
    |
    |

    // creamos el espacio para los objetos de datos de hilo
    hilos_aten=(pthread_t *)malloc(num_hilos_aten*sizeof(pthread_t));

    // Inicializamos los mutex de exclusión a los ficheros de log
    // en que escribirán los workers
    // A RELLENAR
    |
    |
    |
    |

    // Reservamos espacio para los objetos de datos de hilo de los hilos trabajadores
    hilos_work=(pthread_t *)malloc(num_hilos_work*sizeof(pthread_t));

    // Inicializamos la cola
    // A RELLENAR
    |
    |


    // Creamos cada uno de los hilos de atención de peticiones
    for (i=0;i<num_hilos_aten;i++)
    {
        // A RELLENAR
        |
        |
        |
        |
    }
    // Y creamos cada uno de los hilos trabajadores
    for (i=0;i<num_hilos_work;i++)
    {
        // A RELLENAR
        |
        |
        |
        |
    }

    // Esperamos a que terminen todos los hilos
    for (i=0;i<num_hilos_aten;i++)
    {
        pthread_join(hilos_aten[i],NULL);
    }
    for (i=0;i<num_hilos_work;i++)
    {
        pthread_join(hilos_work[i],NULL);
    }
}
