#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#define PACKET_SIZE 1024
#define MAX_USER 10

using namespace std;

WSADATA wsa;
SOCKET sock, client_sock[MAX_USER];
SOCKADDR_IN client[MAX_USER] = { 0 };
int client_size[MAX_USER];

void client_accept();
void recv_client(SOCKET& s, int client_num);

int main() {
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// ----------------------------------------------------

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock, (SOCKADDR*)&addr, sizeof(addr));
	listen(sock, SOMAXCONN);

	thread(client_accept).detach();

	while (1) {

	}

	for (int i = 0; i < MAX_USER; i++)
		closesocket(client_sock[i]);
	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}

void client_accept() {
	char client_num[MAX_USER];
	for (int i = 0; i < MAX_USER; i++) {
		client_size[i] = sizeof(client[i]);
		client_sock[i] = accept(sock, (SOCKADDR*)&client[i], &client_size[i]);

		if (client_sock[i] == INVALID_SOCKET) {
			cout << "ERROR : INVALID SOCKET" << endl;
			closesocket(client_sock[i]);
			closesocket(sock);
			WSACleanup();
			return;
		}

		cout << "CLIENT #" << i << " JOINED TO SERVER !" << endl;

		ZeroMemory(client_num, sizeof(client_num));
		itoa(i, client_num, 10);
		send(client_sock[i], client_num, strlen(client_num), 0);
		thread(recv_client, ref(client_sock[i]), i).detach();
	}
}