#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>

class Client
{
public:
	void Startup();
	static Client* GetInstance();
	std::string user;
	void OnCreate(std::string user_) {
		user = user_;
	}
	Client(const Client&) = delete;
	Client(Client&&) = delete;
	Client& operator=(const Client&) = delete;
	Client& operator=(Client&&) = delete;

private:
	Client(std::string name_);
	Client() {};
	~Client();

	static std::unique_ptr<Client> clientInstance;
	friend std::default_delete<Client>;
};
#endif