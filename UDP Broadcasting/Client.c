#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BROADCAST_PORT 8888
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in broadcast_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len;

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the broadcast address structure
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);    // Set port
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on any IP address

    // Bind the socket to the broadcast address and port
    if (bind(sockfd, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) < 0)
    {
        perror("Binding failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for broadcast messages...\n");

    // Receive broadcast message
    addr_len = sizeof(broadcast_addr);
    while (1)
    {
        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&broadcast_addr, &addr_len);
        if (recv_len < 0)
        {
            perror("Failed to receive broadcast message");
            break;
        }
        buffer[recv_len] = '\0'; // Null-terminate the received message
        printf("Received broadcast message: %s\n", buffer);
    }

    close(sockfd); // Close socket
    return 0;
}