#include <iostream>
#include <winsock2.h>
#define PACKET_SIZE 1024
using namespace std;

SOCKET sock, client_sock;

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// ----------------------------------------------------

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	listen(sock, SOMAXCONN);

	SOCKADDR_IN client = {};
	int client_size = sizeof(client);
	ZeroMemory(&client, client_size);
	client_sock = accept(sock, (SOCKADDR*)&client, &client_size);

	closesocket(client_sock);
	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}