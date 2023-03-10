#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "util.h"

// Función de utilidad que determina si los caracteres de una cadena son todos numericos
int valida_numero(char *str) {
    // A RELLENAR
    |
    |
    |
    |
}

// Función de utilidad que valida si una cadena de caracteres representa una IPv4 valida
int valida_ip(char *ip)
{
    // Comprueba si la cadena contiene una ip válida
    // A RELLENAR
    |
    |
    |
    |
}

// Función de utilidad, para generar los tiempos aleatorios entre un
// min y un max
double randRange(double min, double max)
{
  return min + (rand() / (double) RAND_MAX * (max - min + 1));
}


// Función de utilidad para depuración. Emite por pantalla el mensaje
// que se le pasa como parámetro, pero pone delante del mensaje un
// timestamp, para poder ordenar la salida por si saliera desordenada
//
// Ejemplo de uso:
//
//  log_debug("Mensaje a mostrar por pantalla")
//
void log_debug(char *msg){
  struct timespec t;
  clock_gettime(_POSIX_MONOTONIC_CLOCK, &t);
  printf("[%ld.%09ld] %s", t.tv_sec, t.tv_nsec, msg);
}
