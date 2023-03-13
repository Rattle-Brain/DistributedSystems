#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <sys/types.h>
#include <rpc/rpc.h>

int main(){
	int n = 100;
	char cad = 'F';
	FILE* fich;
	XDR operacion;

	fich = fopen("basicos.dat", "w");
	if(fich == NULL){
		perror("Error al abrir el fichero");
		exit(1);
	}
	xdrstdio_create(&operacion, fich, XDR_ENCODE);
	xdr_int(&operacion, &n);
	xdr_char(&operacion, &cad);
	xdr_destroy(&operacion);
	fclose(fich);
	return 0;
}
