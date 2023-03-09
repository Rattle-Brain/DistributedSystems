#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

// Nos aseguramos de que el hilo padre reconozca la muerte del hijo
void atrapa_sigchld(int s){
	wait(0);
	return;
}


int main(int argc, char* argv[]) {
	int sock_pasivo, sock_datos;
	struct sockaddr_in d_local;
	char buffer[100];
	int leidos;
	pid_t pid;
	int i;

	if(argc < 2){
		printf("Forma de uso: %s <num puerto>\n", argv[0]);
		exit(1);
	}

	signal(SIGCHLD, atrapa_sigchld);
	sock_pasivo = socket(PF_INET, SOCK_STREAM, 0);
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons(atoi(argv[1]));
	bind(sock_pasivo, (struct sockaddr *)&d_local, sizeof(d_local));
	listen(sock_pasivo, SOMAXCONN);
	printf("Soy el proceso padre (%d) antes del while\n", getpid());
	
	//Creamos el pool de procesos aqui
	for (i = 0; i < 3; i++){
		if((pid=fork()) < 0)
			perror("Fallo del fork");
		else if(pid == 0) 
			break;
	}
	

	while (1) { // Bucle infinito de atención a clientes
		printf("Soy el proceso (%d) antes del accept\n", getpid());
		sock_datos = accept(sock_pasivo, 0, 0);
		// Atiende al cliente mientras vengan datos
		while ((leidos=read(sock_datos, buffer, sizeof(buffer))) > 0)
		{

			printf("Soy el proceso (%d) antes del write\n", getpid());
			write(sock_datos, buffer, leidos); // Escribe los datos
			printf("Soy el proceso (%d) despues del write\n", getpid());
		}
		close(sock_datos); // Cierra el socket de datos del proceso cuando termina
	}
}
