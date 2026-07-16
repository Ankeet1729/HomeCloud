#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        exit(EXIT_FAILURE);
    }

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd < 0) {
        perror("Failed to create client socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    int port = std::stoi(argv[1]);
    server.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(client_fd, (sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connection to server failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Connected to server on port: " << port << "\n";

    char buffer[128];
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        perror("Failed to receive server message");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    if(bytes_received < 0) {
        perror("Error");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    std::cout << buffer << "\n";

    std::cout << "You are connected to server\n";

    while(true) {
        char send_buffer[128];
        std::cin.getline(send_buffer, sizeof(send_buffer));
        if (send(client_fd, send_buffer, std::strlen(send_buffer), 0) < 0) {
            perror("Send failed");
            close(client_fd);
            exit(EXIT_FAILURE);
        }

        char recv_buffer[128];
        ssize_t bytes_received = recv(client_fd, recv_buffer, sizeof(recv_buffer) - 1, 0);
        recv_buffer[bytes_received] = '\0';

        std::cout << recv_buffer << "\n";
    }

    close(client_fd);
}
