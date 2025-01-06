#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


//                      QUESTION 4

void send_rrq(int sockfd, const char *filename, const char *mode, struct sockaddr *server_addr, socklen_t server_len) {
    unsigned char rrq[512]; //request
    int len = 0;

    //RRQ code
    rrq[len++] = 0x00;
    rrq[len++] = 0x01; // RRQ

    // file name (ending by 0x00)
    strcpy((char *)&rrq[len], filename);
    len += strlen(filename) + 1;

    //transfer mode
    strcpy((char *)&rrq[len], mode);
    len += strlen(mode) + 1;

    //sending request to server
    ssize_t sent_bytes = sendto(sockfd, rrq, len, 0, server_addr, server_len);
    if (sent_bytes == -1) {
        perror("Error in sending RRQ request");
        exit(EXIT_FAILURE);
    }

     printf("Request RRQ sendt for the file : %s\n", filename);
}