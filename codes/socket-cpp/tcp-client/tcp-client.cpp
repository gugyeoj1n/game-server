#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <thread>
#define PACKET_SIZE 1024
using namespace std;

SOCKET sock;

void proc_recv();

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	// ----------------------------------------------------

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (1) {
		if (!connect(sock, (SOCKADDR*)&addr, sizeof(addr)))
			break;
	}

	thread proc_c(proc_recv);
	char buffer[PACKET_SIZE] = { 0 };

	// MESSAGE SEND
	while (!WSAGetLastError()) {
		cin >> buffer;
		send(sock, buffer, strlen(buffer), 0);
	}

	proc_c.join();

	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}

void proc_recv() {
	char data[PACKET_SIZE] = {};
	string cmd;

	while (!WSAGetLastError()) {
		ZeroMemory(&data, PACKET_SIZE);
		recv(sock, data, PACKET_SIZE, 0);
		cmd = data;

		if (cmd == "exit")
			break;

		cout << "FROM SERVER : " << data << endl;
	}
}