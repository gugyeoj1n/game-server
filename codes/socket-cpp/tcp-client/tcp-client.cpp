#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#define PACKET_SIZE 1024
using namespace std;

SOCKET sock;

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

	while (!WSAGetLastError()) {

	}

	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}