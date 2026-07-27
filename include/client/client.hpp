# pragma once

#include <string>
#include "common/socket.hpp"

class EchoClient {
    

    private:
        Socket socket;
        const std::string server_address;
        const int server_port;
        void connectToServer();
        std::string receiveMessage();
        void sendMessage(const std::string& message);
    
    public:
        EchoClient(const std::string& server_address, const int server_port);
        void start();
};