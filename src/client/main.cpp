#include "client/client.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port>\n";
        return EXIT_FAILURE;
    }

    try {
        std::string server_address = argv[1];
        int server_port = std::stoi(argv[2]);

        EchoClient client(server_address, server_port);
        client.start();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}