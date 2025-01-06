#include <stdlib.h>
#include <stdio.h>
#include "gettftp.h"
#include "rrq.c"


void gettftp(const char *server, const char *filename){

//                      QUESTION 1

    printf("Adresse du serveur : %s\n", server);
    printf("Nom du fichier : %s\n", filename);


//                      QUESTION 4


    //creation of the socket
    
    int sfd;
    struct sockaddr_in server_addr;

    sfd = socket(AF_INET, SOCK_DGRAM, 0);  //UDP socket
    if (sfd == -1) {
        perror("Erreur de création du socket");
        exit(EXIT_FAILURE);
    }

    //setup of the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(69);
    if (inet_pton(AF_INET, server, &server_addr.sin_addr) <= 0) {
        perror("Adresse IP invalide");
        exit(EXIT_FAILURE);
    }

    //call to rrq.c
    
    send_rrq(sfd, filename, "octet", (struct sockaddr *)&server_addr, sizeof(server_addr));

    //closure of the socket
    close(sfd);

}