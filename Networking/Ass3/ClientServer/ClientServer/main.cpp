#include <iostream>
#include "Server.h"
#include "Client.h"

int main(int argc, char** argv) {
	std::string userInput;
	printf("Type 0 if you want to run server || Type 1 if you want to connect as a client\n");
	std::cin >> userInput;

	while (true)
	{
		if (userInput == "0") {
			printf(" > ");
			printf("Created a Server\n");
			Server::GetInstance()->Startup();
			break;
		}
		else if (userInput == "1") {
			printf(" > ");
			printf("Create a display name: ");
			std::cin >> userInput;

			printf(" > ");
			printf("Joined as Client\n");
			Client::GetInstance()->OnCreate(userInput);
			Client::GetInstance()->Startup();
			break;
		}
		else
		{
			printf(" > ");
			printf("Must type 0 if you want to make a server || Type 1 if you want to be a client\n");
			std::cin >> userInput;
		}
	}
	return 0;
}