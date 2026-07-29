# pragma once

#include <string>
#include <vector>
#include <poll.h>
#include "common/socket.hpp"

class EchoServer {
    

    private:
        Socket listenSocket;
        std::vector<Socket> clientSocket;
        std::vector<pollfd> pollFds;
        const int listenPort;
        int acceptClient(Socket& client);
        std::string receiveMessage(Socket& client);
        void sendMessage(const std::string& message, Socket& client);
    
    public:
        EchoServer(const int listenPort);
        void start();
};