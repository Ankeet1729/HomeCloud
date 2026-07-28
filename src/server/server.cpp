#include "server/server.hpp"
#include "common/socket.hpp"

#include <string>
#include <iostream>


EchoServer::EchoServer(const int listenPort) 
    : listenPort(listenPort) {};

void EchoServer::start() {
    listenSocket.listen();
    listenSocket.bind(listenPort);
    std::cout << "Server Listening on port: " << listenPort << "\n";
    acceptClient();
    std::cout << "Client Connected" << "\n";

    const char* hello_msg = "Hello from server\n";
    sendMessage(std::string(hello_msg));

    while(true) {
        std::string receivedMessage = receiveMessage();
        if(receivedMessage == "" or receivedMessage == "exit")
            break;

        sendMessage(receivedMessage);
    } 
}

void EchoServer::acceptClient() {
    acceptSocket.acceptClient(listenSocket.getFd());
}

void EchoServer::sendMessage(const std::string& message) {
    acceptSocket.sendMessage(message);
}

std::string EchoServer::receiveMessage() {
    return acceptSocket.receiveMessage(); 
}