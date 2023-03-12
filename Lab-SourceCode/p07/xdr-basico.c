#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/rpc.h>

void main(){
	int n;
	char* cad;
	FILE* fich;
	XDR operacion;

	fich = fopen("basicos.dat", "w");
	if(fich == NULL){
		perror("Error al abrir el fichero");
		exit(1);
	}
}
