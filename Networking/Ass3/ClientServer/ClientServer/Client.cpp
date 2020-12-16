#define WIN32_LEAN_AND_MEAN

#include "Client.h"
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "4313"
#define DEFAULT_BUFLEN 1024

std::unique_ptr<Client> Client::clientInstance = nullptr;

void Client::Startup() {
	WSADATA wsaData;
	int iResult;
	bool isClientConnected = false;
	SOCKET ConnectSocket = INVALID_SOCKET;


	char sendbuf[] = "test data";
	std::string clientInput;



	struct addrinfo* result = NULL, * ptr = NULL, hints;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		printf("WSAStartup Failed!: %d\n", iResult);
		system("pause");
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);

	if (iResult != 0) {
		printf("getaddinfo failed: %d\n: ", iResult);
		WSACleanup();
		system("pause");
		return;
	}//end if
	else
	{
		isClientConnected = true;
		printf(" > ");
		std::cout << "Connected as |" + user + "| Type \"!LOGOFF\" to disconnect" << std::endl;
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("Socket failed with error: %d\n: ", WSAGetLastError());
			WSACleanup();
			system("pause");
			return;
		}//end if
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}//end if
		break;
	}//end for

	std::thread receiverServerMessage([ConnectSocket, &isClientConnected, &iResult]()
	{
		char recvbuf[1024];
		while (true)
		{
			if (isClientConnected)
			{
				memset(recvbuf, 0, sizeof(recvbuf));
				if (recv(ConnectSocket, recvbuf, sizeof(recvbuf), 0) > 1)
					std::cout << recvbuf << std::endl;
			}
			else std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	});

	do {
		std::getline(std::cin, clientInput);

		if (clientInput._Equal("!LOGOFF"))
		{
			break;
		}

		if (clientInput != "")
		{
			clientInput = "|" + user + "|: " + clientInput;
		}

		iResult = send(ConnectSocket, clientInput.c_str(), clientInput.length() + 1, 0);
		if (iResult == SOCKET_ERROR) {
			printf("Send failed with error: %d\n: ", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			system("pause");
			return;
		}
	} while (iResult > 0);

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		system("pause");
		return;
	}//end if

	closesocket(ConnectSocket);
	WSACleanup();

	printf(" > ");
	std::cout << user + " has disconnected" << std::endl;;
	system("pause");

	return;
}

Client::Client(std::string user_)
{
	user = user_;
}


Client::~Client() {}


Client* Client::GetInstance() {
	if (clientInstance.get() == nullptr) {
		clientInstance.reset(new Client());
	}
	return clientInstance.get();
}