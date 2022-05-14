#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main()
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

	char html[200] = 
	"<!DOCTYPE html>\n"
	"<html lang = \"ja\">\n"
	"<head>\n"
	"<meta charset = \"utf-8\">\n"
	"</head>\n"
	"<body>\n"
	"<h1>hello, world</h1>\n"
	"</body>"
	"</html>";
	char header[200] =	
	"HTTP/1.0 200 OK\n"
	"Content-type: text/html\n"
	"\n";
 
	write(client_socket, header, strlen(header));
	write(client_socket, html, strlen(html));
	close(client_socket);
	close(server_socket);
	return 0;
}

