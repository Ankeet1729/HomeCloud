#include "../../include/client/client.hpp"
#include "../../include/common/socket.hpp"

#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>


EchoClient::EchoClient(const std::string& server_address, const int server_port)
    : server_address(server_address),server_port(server_port), socket() {}

void EchoClient::start() {
    std::cout << "Client Started" << std::endl;
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
