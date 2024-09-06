#include "client.h"

Client::Client(int port, const std::string& name, int secs) :
    _port(port),
    _name(name),
    _secs(secs)
{
    _sizeName = _name.size();
}

void Client::start()
{
    while (1)
    {
        connectToServer();
        std::this_thread::sleep_for(std::chrono::seconds(_secs));
    }
}

void Client::connectToServer()
{
    int _sock = socket(AF_INET, SOCK_STREAM, 0);

    if (_sock < 0)
    {
        std::cout << "Error: cannot create server socket\n";
        return;
    }

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(_sock, (sockaddr*)&_addr, sizeof(_addr)) < 0)
    {
        std::cout << "Error: cannot connect socket\n";
        return;
    }

    send(_sock, (char*)&_sizeName, sizeof(_sizeName), 0);
    send(_sock, _name.c_str(), _sizeName, 0);
    close(_sock);
}
