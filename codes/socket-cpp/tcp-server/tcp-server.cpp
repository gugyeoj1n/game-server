#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#define PACKET_SIZE 1024

using namespace std;

WSADATA wsa;
SOCKET sock, *client_sock;
SOCKADDR_IN *client;
int *client_size, MAX_USER, CNT_USER;

void client_accept();
void recv_client(SOCKET& s, int client_num);

int main() {
	int PORT;
	cout << "SET PORT >> ";
	cin >> PORT;
	cout << "\nSET MAX COUNT OF USER >> ";
	cin >> MAX_USER;

	client_sock = new SOCKET[MAX_USER];
	client = new SOCKADDR_IN[MAX_USER];
	client_size = new int[MAX_USER];
	CNT_USER = 0;

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

	cout << "\n\n---------------------------------\n" 
		<< "  SERVER OPEN !\n"
		<< "  MESSAGE COMMAND : |  exit  |  mem  |\n" 
		<< "  TARGET COMMAND : |  all  |\n" 
		<< "-------------------------------- - \n\n";


	// SERVER CAN SEND MESSAGE TO CLIENT
	char msg[PACKET_SIZE], send_num[PACKET_SIZE];
	while (1) {
		cout << "\n  INPUT SERVER MESSAGE >> ";
		cin.getline(msg, PACKET_SIZE, '\n');

		if (!strcmp(msg, "exit"))
			break;
		else if (!strcmp(msg, "mem")) {
			cout << "  MEMBER COUNT >> " << CNT_USER << " / " << MAX_USER << endl;
			continue; 
		}

		cout << "\n  TARGET CLIENT >> ";
		cin.getline(send_num, PACKET_SIZE, '\n');

		if (!strcmp(send_num, "all")) {
			for (int i = 0; i < MAX_USER; i++)
				send(client_sock[i], msg, strlen(msg), 0);
		}
		else
			send(client_sock[atoi(send_num)], msg, strlen(msg), 0);
	}

	for (int i = 0; i < MAX_USER; i++)
		closesocket(client_sock[i]);
	closesocket(sock);

	// ----------------------------------------------------
	WSACleanup();

	delete[] client_sock, client, client_size;
	return 0;
}

void client_accept() {
	char *client_num = new char[MAX_USER];
	for (int i = 0; i < MAX_USER; i++) {
		client_size[i] = sizeof(client[i]);
		client_sock[i] = accept(sock, (SOCKADDR*)&client[i], &client_size[i]);

		if (client_sock[i] == INVALID_SOCKET) {
			cout << "  ERROR : INVALID SOCKET" << endl;
			closesocket(client_sock[i]);
			closesocket(sock);
			WSACleanup();
			return;
		}

		cout << "\n  CLIENT #" << i << " JOINED TO SERVER !\n" << "  INPUT SERVER MESSAGE >> ";
		CNT_USER++;
		ZeroMemory(client_num, sizeof(client_num));
		_itoa(i, client_num, 10);
		send(client_sock[i], client_num, strlen(client_num), 0);
		thread(recv_client, ref(client_sock[i]), i).detach();
	}
}

void recv_client(SOCKET& s, int client_num) {
	char buf[PACKET_SIZE];

	while (!WSAGetLastError()) {
		ZeroMemory(buf, PACKET_SIZE);
		recv(s, buf, PACKET_SIZE, 0);

		cout << "\n  CLIENT[" << client_num << "] >> " << buf << "\n  INPUT SERVER MESSAGE >> ";
	}

	cout << "\n  CLIENT #" << client_num << " DISCONNECTED !" << "\n  INPUT SERVER MESSAGE >> ";
	CNT_USER--;
	return;
}