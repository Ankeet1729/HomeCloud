#include "server/server.hpp"
#include "common/socket.hpp"

#include <string>
#include <iostream>


EchoServer::EchoServer(const int listenPort) 
    : listenPort(listenPort) {};

void EchoServer::start() {
    listenSocket.create();
    listenSocket.bind(listenPort);
    listenSocket.listen();
    std::cout << "Server Listening on port: " << listenPort << "\n";
    acceptClient();
    std::cout << "Client Connected" << "\n";

    const char* hello_msg = "Hello from server\n";
    sendMessage(std::string(hello_msg));

    while(true) {
        std::string receivedMessage = receiveMessage();
        if(receivedMessage == "" or receivedMessage == "exit") {
            std::cout << "Exiting.." << "\n";
            break;
        }
        std::cout << "Client sent message: " << receivedMessage << ".. Echoing back" << "\n";

        sendMessage(receivedMessage);
    } 
}

void EchoServer::acceptClient() {
    int fd = listenSocket.acceptClient();
    acceptSocket.create(fd);
}

void EchoServer::sendMessage(const std::string& message) {
    acceptSocket.sendMessage(message);
}

std::string EchoServer::receiveMessage() {
    return acceptSocket.receiveMessage(); 
}