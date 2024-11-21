#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(SERVER_PORT); 
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid server address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type 'exit' to end the chat.\n");


    while (1) {

        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), 0, 
               (const struct sockaddr *)&server_addr, addr_len);

        if (strcmp(buffer, "exit") == 0) {
            printf("Chat ended by you.\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        buffer[n] = '\0';  
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }

    // Close the socket
    close(sockfd);

    return 0;
}
