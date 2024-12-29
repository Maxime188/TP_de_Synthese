#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 500

int main(int argc, char *argv[]){
    int              sfd, s;
    char             buf[BUF_SIZE];
    size_t           len;
    ssize_t          nread;
    struct addrinfo  hints;
    struct addrinfo  *result, *rp;
    char ipstr[INET6_ADDRSTRLEN]; //to stock the address

    if (argc < 3) {
        fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Obtain address(es) matching host/port. */

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;          /* Any protocol */

    s = getaddrinfo(argv[1], argv[2], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    /* getaddrinfo() returns a list of address structures.
        Try each address until we successfully connect(2).
        If socket(2) (or connect(2)) fails, we (close the socket and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) {  // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr; //conversion of the binary address 
            inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
             printf("Adresse IPv4 du serveur : %s\n", ipstr);
        }
        else if (rp->ai_family == AF_INET6) {  // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)rp->ai_addr;
            inet_ntop(AF_INET6, &(ipv6->sin6_addr), ipstr, sizeof(ipstr));
            printf("Adresse IPv6 du serveur : %s\n", ipstr);
        }

        //socket creation :

        
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1) {
            perror("socket");
            continue;
        }
        

       //connexion to the server :
       
       
        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) == -1) {
            close(sfd);
            perror("connect");
            continue;
        }
        

    }
   

    freeaddrinfo(result);           /* No longer needed */

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not connect\n");
        exit(EXIT_FAILURE);
    }
    printf("Succès\n");

    //closure of the socket after using it :

    close(sfd);
    return 0;

}