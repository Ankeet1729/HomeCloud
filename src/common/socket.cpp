#include "common/socket.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>
#include <cstring>
#include <iostream>

Socket::Socket() {
    this->fd = -1;
}

Socket::~Socket() {  // TODO: changes need to be done when move semantics are implemented
    if(this->fd >= 0)
        close(this->fd);
}

Socket::Socket(Socket&& other) {
    this->fd = other.fd;
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
    if(this != &other) {
        if(this->fd >= 0)
            close(this->fd);

        this->fd = other.fd;

        other.fd = -1;
    }

    return *this;
}

void Socket::create() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->fd < 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

void Socket::create(int assignFd) {
    if(this->fd >= 0)
        close(this->fd);

    this->fd = assignFd;
}

int Socket::getFd() const {
    return this->fd;
}

void Socket::connectToServer(const std::string& server_address, int server_port) {
    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    int result = inet_pton(AF_INET, server_address.c_str(), &server.sin_addr);

    if (result < 0) {
        throw std::runtime_error(std::strerror(errno));
    }

    else if(result == 0) {
        throw std::runtime_error("Invalid IPv4 address");
    }

    if (connect(this->fd, (sockaddr*)&server, sizeof(server)) < 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

void Socket::bind(int port) {
    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if(::bind(this->fd, (sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error(std::strerror(errno));
    }
}

void Socket::listen() {
    if(::listen(this->fd, 3) < 0) {      // ::listen for taking from global namespace, 3 is the max kernel backlog queue for now
        throw std::runtime_error(std::strerror(errno));
    }
}

int Socket::acceptClient() { // TODO: Note that accepted socket replaces an already-existing Socket object.. Do something about it later
    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int fd = accept(this->fd, (sockaddr*)&client_addr, &client_len);

    if (fd < 0) {
        throw std::runtime_error(std::strerror(errno));
    }

    return fd;
}

void Socket::sendMessage(const std::string& message) {
    const char* m = message.c_str();

    if (send(this->fd, m, std::strlen(m), 0) < 0) {
        throw std::runtime_error(std::strerror(errno));
    } 
}

std::string Socket::receiveMessage() {
    char recv_buffer[128];
    ssize_t bytes_received = recv(this->fd, recv_buffer, sizeof(recv_buffer) - 1, 0);

    if(bytes_received < 0) {
            throw std::runtime_error(std::strerror(errno));
        }
    else if (bytes_received == 0) {
        return "";
    }

    recv_buffer[bytes_received] = '\0';

    return std::string(recv_buffer, bytes_received);
}

