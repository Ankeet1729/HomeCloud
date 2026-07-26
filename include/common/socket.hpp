# pragma once

class Socket {
    private:
        const int fd;

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
};