#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int sock_pasivo, sock_datos;
	struct sockaddr_in d_local;
	char buffer[100];
	int leidos;

	sock_pasivo = socket(PF_INET, SOCK_STREAM, 0);
	d_local.sin_family = AF_INET;
	d_local.sin_addr.s_addr = htonl(INADDR_ANY);
	d_local.sin_port = htons(7890);
	bind(sock_pasivo, (struct sockaddr *)&d_local, sizeof(d_local));
	listen(sock_pasivo, SOMAXCONN);
	
	while (1) { // Bucle infinito de atención a clientes
		sock_datos = accept(sock_pasivo, 0, 0);
		while ((leidos=read(sock_datos, buffer, sizeof(buffer))) > 0){
			write(sock_datos, buffer, leidos);
		}
		close(sock_datos);
	}
}
