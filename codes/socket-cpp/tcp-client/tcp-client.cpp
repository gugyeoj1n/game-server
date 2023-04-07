#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <thread>
#define PACKET_SIZE 1024
using namespace std;

SOCKET sock;

void recv_data(SOCKET& s);

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

	// FIRST RECV, RENAME CONSOLE TITLE
	char buf[PACKET_SIZE];
	TCHAR new_title[PACKET_SIZE];
	recv(sock, buf, PACKET_SIZE, 0);
	sprintf(buf, "[%d] %s:%d", atoi(buf), inet_ntoa(addr.sin_addr), htons(addr.sin_port));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, buf, strlen(buf), new_title, 256);
	SetConsoleTitle(new_title);

	thread(recv_data, ref(sock)).detach();

	while (!WSAGetLastError()) {
		cout << "INPUT YOUR MESSAGE >> ";
		cin >> buf;

		send(sock, buf, strlen(buf), 0);
	}

	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}

void recv_data(SOCKET& s) {
	char buf[PACKET_SIZE];

	while (1) {
		ZeroMemory(buf, PACKET_SIZE);
		recv(s, buf, PACKET_SIZE, 0);

		if (WSAGetLastError()) break;

		cout << "\n[ Server ] >> " << buf << endl;
	}
}