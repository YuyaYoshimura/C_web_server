#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define HTML_FILE argv[1]

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("正しい使用法を確認してください\n");
	}

	struct sockaddr_in server;
 	struct sockaddr_in client;

 	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {
		printf("問題が発生しました\n");
		return 1;
	}

 	server.sin_family = AF_INET;
 	server.sin_port = htons(12345);
 	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) == -1) {
		printf("問題が発生しました\n");
		return 1;
	}

	if (listen(server_socket, 5) == -1) {
		printf("問題発生しました\n");
		return 1;
	}
	
	socklen_t len;
	len = sizeof(client);	
	int client_socket = accept(server_socket, (struct sockaddr *)&client, &len);
	if (client_socket == -1) {
		printf("問題発生しました\n");
		return 1;
	}
	
	FILE *file;
	file = fopen(HTML_FILE, "r");
	if (file == NULL) {
		printf("問題が発生しました\n");
		return 1;
	}

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
 
	if (write(client_socket, header, strlen(header)) == -1) {
		printf("問題が発生しました\n");
		return 1;
	}
	if (write(client_socket, html_source, strlen(html_source)) == -1) {
		printf("問題が発生しました\n");
		return 1;
	}

	if (close(client_socket) == -1) {
		printf("問題が発生しました\n");
		return 1;
	}
	if (close(server_socket) == -1) {
		printf("問題が発生しました\n");
		return 1;
	}

	return 0;
}

