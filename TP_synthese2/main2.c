#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 500

void send_rrq(int sockfd, const char *filename, const char *mode, struct sockaddr *server_addr, socklen_t server_len);


int main(int argc, char *argv[])
{
    int sfd, s;
    char buf[BUF_SIZE];
    size_t len;
    ssize_t nread;
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    char ipstr[INET6_ADDRSTRLEN]; // to stock the address

    if (argc < 3)
    {
        fprintf(stderr, "Use: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port. */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

 

        // socket creation :

        sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sfd == -1)
        {
            perror("socket");
            exit(EXIT_FAILURE);
        }

 
 
    // closure of the socket after using it :

    send_rrq(sfd, argv[3], "octet", result->ai_addr, result->ai_addrlen);

    receive_data_and_ack(sfd, result->ai_addr, result->ai_addrlen);
    
    close(sfd);
    return 0;
}