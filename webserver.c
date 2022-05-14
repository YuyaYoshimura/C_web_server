#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HTML_FILE argv[1]

int main(int argc, char* argv[])
{
	struct sockaddr_in server;
 	struct sockaddr_in client;

 	int server_socket = socket(AF_INET, SOCK_STREAM, 0);

 	server.sin_family = AF_INET;
 	server.sin_port = htons(12345);
 	server.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *)&server, sizeof(server));

	listen(server_socket, 5);
	
	socklen_t len;
	len = sizeof(client);	
	int client_socket = accept(server_socket, (struct sockaddr *)&client, &len);
	
	FILE *file;
	file = fopen(HTML_FILE, "r");
	char html_source[1024];
	char tmp[1024];
	html_source[0] = '\0';
	while (fscanf(file, "%s", tmp) != EOF) {
		strcat(html_source, tmp);
	}
				
	char header[200] =	
	"HTTP/1.0 200 OK\n"
	"Content-type: text/html\n"
	"\n";
 
	write(client_socket, header, strlen(header));
	write(client_socket, html_source, strlen(html_source));
	close(client_socket);
	close(server_socket);
	return 0;
}

