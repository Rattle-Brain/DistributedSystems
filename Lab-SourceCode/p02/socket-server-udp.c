#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
	int sock_dat, recibidos;
	struct sockaddr_in d_local, d_cliente;
	socklen_t ldir = sizeof(d_cliente);
	char buffer[50];
	
	sock_dat = socket(PF_INET, SOCK_DGRAM, 0);
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons(7890);
	bind(sock_dat, (struct sockaddr *)&d_local, sizeof(d_local));
	
	while (1) { // Bucle infinito de atención a clientes
		recibidos = recvfrom(sock_dat, buffer, sizeof(buffer), 0,
		(struct sockaddr *) &d_cliente, &ldir);
		printf("Cliente desde %s (%d)\n",
		inet_ntoa(d_cliente.sin_addr), ntohs(d_cliente.sin_port));
		sendto(sock_dat, recibidos, strlen(mensaje), 0,
		(struct sockaddr *) &d_cliente, ldir);
	}
}
