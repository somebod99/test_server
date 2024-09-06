#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string>
#include <thread>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <mutex>

constexpr int listen_count = 10;

class Server
{
public:
    enum class STATUS
    {
        EMPTY,
        BIND,
        LISTEN
    };

    Server(int port);
    ~Server();

    void start();

    inline bool started() { return _status == STATUS::LISTEN; }
    inline bool binded() {  return _status == STATUS::BIND; }

private:
    void log(const std::string& msg);
    void handleClient(int client_sock);

private:
    std::ofstream _logFile;
    std::mutex _logMutex;
    int _sock;
    STATUS _status = STATUS::EMPTY;
};

#endif // SERVER_H
