#include "client.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Error: number of arguments must be equal 3\n";
        return -1;
    }

    std::string name = argv[1];
    int port = atoi(argv[2]);
    int secs = atoi(argv[3]);

    Client client(port, name, secs);
    client.start();

    return 0;
}
