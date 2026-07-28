#include "client/client.hpp"
#include "common/socket.hpp"

#include <string>
#include <iostream>


EchoClient::EchoClient(const std::string& server_address, const int server_port)
    : server_address(server_address),server_port(server_port), socket() {}

void EchoClient::start() {
    connectToServer();
    std::cout << receiveMessage() << "\n";

    while(true) {
        char send_buffer[128];
        std::cin.getline(send_buffer, sizeof(send_buffer)); 
        std::string message(send_buffer);
        sendMessage(message);

        if(message == "exit")
            break;

        std::string receivedMessage = receiveMessage(); 
        std::cout << receivedMessage << "\n"; 
        
    }
}

void EchoClient::connectToServer() {
    socket.connectToServer(this->server_address, this->server_port);
}

void EchoClient::sendMessage(const std::string& message) {
    socket.sendMessage(message);
}


std::string EchoClient::receiveMessage() {
    return socket.receiveMessage(); 
}
