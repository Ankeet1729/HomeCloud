# pragma once

#include <string>
#include <vector>
#include "../common/socket.hpp"

class EchoServer {
    

    private:
        Socket listenSocket;
        Socket acceptSocket;
        void acceptClient();
        std::string receiveMessage();
        void sendMessage(const std::string& message);
        const int listenPort;
    
    public:
        EchoServer(const int listenPort);
        void start();
};