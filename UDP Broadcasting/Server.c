#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BROADCAST_PORT 8888
#define BROADCAST_IP "192.168.1.255" // Broadcast address for class C network

int main()
{
    int sockfd;
    struct sockaddr_in broadcast_addr;
    int broadcast_permission = 1; // Enable broadcast option
    char message[] = "Broadcast message from server";

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options to allow broadcasting
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_permission, sizeof(broadcast_permission)) < 0)
    {
        perror("Setting broadcast permission failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Define the broadcast address structure
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(BROADCAST_PORT);          // Set port
    broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP); // Set broadcast IP

    // Send the broadcast message
    if (sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr)) < 0)
    {
        perror("Broadcast message failed to send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Broadcast message sent.\n");

    close(sockfd); // Close socket
    return 0;
}