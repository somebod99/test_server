#include "server.h"

Server::Server(int port)
{
    _logFile.open("log.txt", std::ios::out | std::ios::app);

    sockaddr_in addr;

    _sock = socket(AF_INET, SOCK_STREAM, 0);

    if (_sock < 0)
    {
        log("Error: cannot create server socket\n");
        return;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(_sock, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        log("Error: cannot bind socket\n");
        return;
    }

    _status = STATUS::BIND;
}

Server::~Server()
{
    _logFile.close();
}

void Server::start()
{
    if (_status != STATUS::BIND)
        return;

    _status = STATUS::LISTEN;
    listen(_sock, listen_count);

    while (1)
    {
        int client_sock = accept(_sock, nullptr, nullptr);
        std::thread([this, client_sock=client_sock](){handleClient(client_sock);}).detach();
    }
}

void Server::log(const std::string &msg)
{
    const auto now = std::chrono::system_clock::now();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    const auto now_t = std::chrono::system_clock::to_time_t(now);

    std::lock_guard<std::mutex> lg(_logMutex);
    _logFile << "[" << std::put_time(std::localtime(&now_t), "%F %T.") << std::setfill('0') << std::setw(3) << ms.count() << "] " << msg << "\n";
    _logFile.flush();
}

void Server::handleClient(int client_sock)
{
    int size;
    int ans = recv(client_sock, (char*)&size, sizeof(size), 0);

    if (!ans)
    {
        log("Error: cannot receive data size from client socket\n");
        close(client_sock);
        return;
    }

    char* buffer = new char[size];
    ans = recv(client_sock, (char*)buffer, size, 0);

    if (!ans)
    {
        log("Error: cannot receive data from client socket\n");
        close(client_sock);
        return;
    }

    log(buffer);
    delete[] buffer;
    close(client_sock);
}
