#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <thread>
#define PACKET_SIZE 1024
using namespace std;

SOCKET sock, client_sock;

void proc_recvs();

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

	char buffer[PACKET_SIZE] = { 0 };
	thread proc_s(proc_recvs);

	while (!WSAGetLastError()) {
		cin >> buffer;
		send(client_sock, buffer, strlen(buffer), 0);
	}

	proc_s.join();

	closesocket(client_sock);
	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}

void proc_recvs() {
	char data[PACKET_SIZE] = {};

	while (!WSAGetLastError()) {
		ZeroMemory(&data, PACKET_SIZE);
		recv(sock, data, PACKET_SIZE, 0);

		cout << "FROM CLIENT : " << data << endl;
	}
}