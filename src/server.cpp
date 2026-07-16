#include <sys/socket.h>
#include <netinet/in.h>
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

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("Failed to create server socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address{};
    address.sin_family = AF_INET;
    int port = std::stoi(argv[1]);
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);

    if (client_fd < 0) {
        perror("Accept Failed");
        close(server_fd);
        return 1;
    }

    std::cout << "Accepted incoming client connection\n";

    const char* hello_msg = "Hello from server\n";
    if (send(client_fd, hello_msg, std::strlen(hello_msg), 0) < 0) {
        perror("Send failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    } 

    while(true) {
        char recv_buffer[128];
        ssize_t bytes_received = recv(client_fd, recv_buffer, sizeof(recv_buffer) - 1, 0);
        if(bytes_received < 0) {
            perror("Error");
            close(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        if(bytes_received == 0) {
            std:: cout << "Client Disconnected\n";
            break; 
        }
        recv_buffer[bytes_received] = '\0';

        std::cout << "Received from client: " << recv_buffer << "... Echoing back\n";

        if (send(client_fd, recv_buffer, bytes_received, 0) < 0) {
            perror("Send failed");
            close(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    close(client_fd);
    close(server_fd);
}
