/*
EPI GIJÓN
GRADO EN INGENIERIA INFORMATICA
SISTEMAS DISTRIBUIDOS - CURSO 3º
MATERIAL DE LA ASIGNATURA
-------------------------
MECANISMO   : PIPES
FICHERO     : whosort.c
DESCRIPCION : Implementacion del proceso de usuario who | sort empleando
pipes.
*/
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


int main(void)
{
  int fds[2];
  pipe(fds);          /*Crea un pipe */
  /* El primer hijo reconecta su entrada standard (stdin) al flujo de
  salida del pipe y cierra su descriptor de la entrada del pipe */
  if (fork()  == 0) {
    dup2(fds[0], 0);
    close(fds[1]);
    execlp("sort", "sort", NULL);
  }
  /* El segundo hijo reconecta su salida standard (stdout) a la entrada
  del pipe y cierra el descriptor de la salida del pipe */
  else if ( fork() == 0) {
    dup2(fds[1], 1);
    close(fds[0]);
    execlp("who", "who", NULL);
  }
  /*El padre cierra ambos descriptores del pipey espera la finalizacion
  de sus hijos */
  else {
    close(fds[0]);
    close(fds[1]);
    wait(0);
    wait(0);
  }
  return 1;
}
