#include<stdio.h>
int main (){
	char dato;
	char *p = &dato;

	printf("valor del puntero p: %p\n", p);
	printf("Resultado de p+1: %p\n", p+1);
}
