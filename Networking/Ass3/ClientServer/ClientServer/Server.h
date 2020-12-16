#ifndef SERVER_H
#define SERVER_H

#include <iostream>

class Server
{
public:
	void Startup();
	static Server* GetInstance();
	Server(const Server&) = delete;
	Server(Server&&) = delete;
	Server& operator=(const Server&) = delete;
	Server& operator=(Server&&) = delete;

private:
	Server();
	~Server();

	static std::unique_ptr<Server> serverInstance;
	friend std::default_delete<Server>;
};
#endif
