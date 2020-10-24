#include <iostream>
#include <WS2tcpip.h>
#include <vector>

// Include the Winsock library (lib) file
#pragma comment (lib, "ws2_32.lib")


void main(int argc, char* argv[]) // We can pass in a command line option!! 
{
	////////////////////////////////////////////////////////////
	// INITIALIZE WINSOCK
	////////////////////////////////////////////////////////////

	// Structure to store the WinSock version. This is filled in
	// on the call to WSAStartup()
	WSADATA data;

	// To start WinSock, the required version must be passed to
	// WSAStartup(). This server is going to use WinSock version
	// 2 so I create a word that will store 2 and 2 in hex i.e.
	// 0x0202
	WORD version = MAKEWORD(2, 2);

	// Start WinSock
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		// Not ok! Get out quickly
		std::cout << "Can't start Winsock! " << wsOk;
		return;
	}

	////////////////////////////////////////////////////////////
	// CONNECT TO THE SERVER
	////////////////////////////////////////////////////////////

	// Socket creation, note that the socket type is datagram
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);

	// Create a hint structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET; // AF_INET = IPv4 addresses
	server.sin_port = htons(54000); // Little to big endian conversion
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // Convert from string to byte array


	// Write out to that socket
	std::vector<std::string> stringVector;
	char max[255];
	char buf[1024];
	bool isRunning = true;
	int counter = 1;
	int serverLength = sizeof(server);

	while (isRunning) {
		printf(" > ");
		std::cin >> max;

		if (!strcmp(max, "!SEND")) {

			for (auto i : stringVector) {
				printf(i.c_str());
				printf("\n");

				int sendOk = sendto(out, i.c_str(), i.size() + 1, 0, (sockaddr*)&server, sizeof(server));
				if (sendOk == SOCKET_ERROR) {
					std::cout << "That didn't work! " << WSAGetLastError() << std::endl;
				}

				int bytesIn = recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
				if (bytesIn == SOCKET_ERROR) {
					printf("Error receiving from client ", WSAGetLastError());
					printf("\n");
					continue;
				}
				else {
					printf(buf);
					printf("\n");
					ZeroMemory(buf, 1024); // Clear the receive buffer
				}
			}
			counter = 1;
			stringVector.clear();
		}
		else if (!strcmp(max, "!EXIT")) {
			isRunning = false;
			for (auto i : max) {
				i = NULL;
			}
		}
		else {
			stringVector.push_back(max);
			counter++;
		}
	}

	// Close the socket
	closesocket(out);

	// Close down Winsock
	WSACleanup();
}