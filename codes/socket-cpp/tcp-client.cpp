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

	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();
}