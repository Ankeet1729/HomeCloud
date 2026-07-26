# pragma once

#include <string>

class Socket {
    private:
        int fd;

    public:
        Socket();
        ~Socket();

        // Prevent copying because a file descriptor has a single owner
        Socket(const Socket&) = delete; 
        Socket& operator=(const Socket&) = delete;

        Socket(Socket&&);
        Socket& operator=(Socket&&);

        // Promising the compiler that we won't change any data member
        int getFd() const;

        void connectToServer(const std::string& server_address, int server_port);
        void sendMessage(const std::string& message);
        std::string receiveMessage();
};