#include <stdio.h> // Para FILE*
#include <errno.h> // para perror()
#include <stdlib.h> // para exit()
#include <rpc/types.h>
#include <rpc/xdr.h>

#define DEFAULT_INTEGER_VALUE 100
#define DEFAULT_CHAR_VALUE 'A'

int main(){
	int n;
	char cad; 
	FILE* fich;
	XDR operacion;

	fich = fopen("basicos.dat", "w");
	if(fich == NULL){
		perror("Error al abrir el fichero");
		exit(1);
	}
	// Init XDR filter
	// xdrstdio_create(&operacion, fich, XDR_ENCODE);
	
	// Ask the user for values
	printf("Enter an integer:\n");
	scanf("%d", &n);
	if (n < 0){
		perror("The value is not valid, setting default");
		n = DEFAULT_INTEGER_VALUE;
	}
	printf("Enter a char:\n");
	scanf("%s", &cad);
	if(sizeof(char)/sizeof(cad) != 1){
		perror("CHAR cannot be null or longer than 1, setting default");
		cad = DEFAULT_CHAR_VALUE;
	}


	// Store Values into file
	xdr_int(&operacion, &n);
	xdr_char(&operacion, &cad);

	// Destroy and close to exit program
	xdr_destroy(&operacion);
	fclose(fich);
	return 0;
}
