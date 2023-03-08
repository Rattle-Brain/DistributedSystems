/*
EPI GIJÓN
GRADO EN INGENIERIA INFORMATICA
SISTEMAS DISTRIBUIDOS - CURSO 3º
MATERIAL DE LA ASIGNATURA
-------------------------
MECANISMO   : PIPES
FICHERO     : prodcons.c
DESCRIPCION : Se propone la realizacion de un programa en el que dos
procesos se envien a traves de un pipe un fichero de texto donde 
el que recibe debe mostrarlo por su salida standard.
*/
#include <unistd.h>
#include <stdio.h>
int main()
{
    int fds[2];
    pipe(fds);                  /*Crea un pipe */
	pid_t pid;
    /* Este proceso debera enviar el fichero al otro proceso a traves
       del pipe.
    */
    if ((pid=fork()) == 0) {
      /*Añadir algo */ 
    }
    /* Este otro proceso es el que se debe encargar de obtener el
       fichero del pipe y mostrarlo por su salida standard. 
    */
    else if ((pid=fork()) == 0) {
      /*Añadir algo */  
    }
    /*El padre cierra ambos descriptores del pipe
        y espera la finalizacion de sus hijos 
    */
    else {
     /* Añadir algo */
    }
}
