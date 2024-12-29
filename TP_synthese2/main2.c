#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gettftp.h"
#include "puttftp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    if (argc<4){
        printf("Usage: %s [gettftp|puttftp] <server> <file>\n", argv[0]);
        return 1;
    }


    const char *command = argv[1];
    const char *server = argv[2];
    const char *filename = argv[3];

    if (strcmp(command, "gettftp")==0){
        gettftp(server, filename);
        return 0;
    }

    else if (strcmp(command, "puttftp")==0){
        puttftp(server, filename);
        return 0;
    }
    else{
        printf("Commande inconnue: %s \n", command);
        return 1;
    }
    return 0;

    

    const char *hostname = "serveur";
    const char *port = "80";

    struct addrinfo hints, *res, *p;
    int status;

    //Initialization of hints structure
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;         // IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;     // Socket UDP

    status = getaddrinfo(hostname, port, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // Parcourir les résultats
    printf("Adresses pour %s:\n", hostname);
    for (p = res; p != NULL; p = p->ai_next) {
        char ipstr[INET6_ADDRSTRLEN];
        void *addr;
        char *ipver;
        // Obtenir le pointeur vers l'adresse (IPv4 ou IPv6)
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        // Convertir l'adresse en chaîne de caractères
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("  %s: %s\n", ipver, ipstr);
    }

    // Libérer la mémoire allouée par getaddrinfo
    freeaddrinfo(res);

    return 0;
}