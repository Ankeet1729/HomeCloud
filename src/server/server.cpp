#include "server/server.hpp"
#include "common/socket.hpp"

#include <string>
#include <iostream>


EchoServer::EchoServer(const int listenPort) 
    : listenPort(listenPort) {};

void EchoServer::start() {
    listenSocket.listen(listenPort);
    std::cout << "Server Started" << std::endl;
}

void EchoServer::acceptClient() {
    acceptSocket.acceptClient();
}

void EchoServer::sendMessage(const std::string& message) {
    acceptSocket.sendMessage(message);
}

std::string EchoServer::receiveMessage() {
    return acceptSocket.receiveMessage(); 
}