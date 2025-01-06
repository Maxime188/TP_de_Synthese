#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 516

void receive_data_and_ack(int sfd, struct sockaddr *server_addr, socklen_t server_len) {

    int sfd;

    unsigned char buf[BUF_SIZE];  //buffer to stock data
    ssize_t nread;
    nread = recvfrom(sfd, buf, BUF_SIZE, 0, result->ai_addr, result->ai_addrlen);
    if (nread == -1) {
        perror("Erreur de réception");
        exit(EXIT_FAILURE);
    }

    printf("Data Packet (DAT) received, lenght : %zd\n", nread);
    unsigned char ack[4];
    ack[0] = 0x00;  // ACK (0x04)
    ack[1] = 0x04;
    ack[2] = buf[2];  //number of ACK packet received
    ack[3] = buf[3];  //number of ACK packet received

    ssize_t sent_bytes = sendto(sfd, ack, sizeof(ack), 0, result->ai_addr, result->ai_addrlen);
    if (sent_bytes == -1) {
        perror("Error in ACK sending");
        exit(EXIT_FAILURE);
    }
    printf("ACK sendt for the block %d\n", (buf[2] << 8) + buf[3]);

}