#include "server.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Error: number of arguments must be equal 1\n";
        return -1;
    }

    int port = stoi(argv[1]);
    Server server(port);
    if (!server.binded())
    {
        std::cout << "Error: server was not binded\n";
        return -2;
    }

    server.start();
    if (!server.started())
    {
        std::cout << "Error: server was not started\n";
        return -3;
    }

    return 0;
}
