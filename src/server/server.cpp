#include "server/server.hpp"
#include "common/socket.hpp"

#include <string>
#include <poll.h>
#include <iostream>


EchoServer::EchoServer(const int listenPort) 
    : listenPort(listenPort) {};

void EchoServer::start() {
    listenSocket.create();
    listenSocket.bind(listenPort);
    listenSocket.listen();
    struct pollfd listenPoll{};
    listenPoll.fd = listenSocket.getFd();
    listenPoll.events = POLLIN;
    pollFds.push_back(listenPoll);
    std::cout << "Server Listening on port: " << listenPort << "\n";

    while(true) {
        int ready = poll(pollFds.data(), pollFds.size(), -1);

        if (ready < 0)
            throw std::runtime_error("poll() failed");

        if(pollFds[0].revents & POLLIN) {
            clientSocket.emplace_back();
            struct pollfd acceptPoll{};
            acceptPoll.events = POLLIN;
            acceptPoll.fd = acceptClient(clientSocket.back());
            pollFds.push_back(acceptPoll);
        }

        for(int i = 1; i<pollFds.size(); i++) {
            if(pollFds[i].revents & POLLIN) {
                std::string receivedMessage = receiveMessage(clientSocket[i-1]);
                sendMessage(receivedMessage, clientSocket[i-1]);
            }
        }
    }

    // int fd = acceptClient();
    // std::cout << "Client Connected" << "\n";

    // const char* hello_msg = "Hello from server\n";
    // sendMessage(std::string(hello_msg), fd);

    // while(true) {
    //     std::string receivedMessage = receiveMessage(fd);
    //     if(receivedMessage == "" or receivedMessage == "exit") {
    //         std::cout << "Exiting.." << "\n";
    //         break;
    //     }
    //     std::cout << "Client sent message: " << receivedMessage << ".. Echoing back" << "\n";

    //     sendMessage(receivedMessage, fd);
    // } 
}

int EchoServer::acceptClient(Socket& client) {
    int fd = listenSocket.acceptClient();
    client.create(fd);
    return fd;
}

void EchoServer::sendMessage(const std::string& message, Socket& client) {
    client.sendMessage(message);
}

std::string EchoServer::receiveMessage(Socket& client) {
    return client.receiveMessage(); 
}