#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string>
#include <thread>
#include <chrono>

class Client
{
public:
    Client(int port, const std::string& name, int secs);
    void start();

private:
    void connectToServer();

private:
    int _sock;
    sockaddr_in _addr;
    int _port;
    std::string _name;
    int _sizeName;
    int _secs;
};

#endif // CLIENT_H
