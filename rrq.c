#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


//                      QUESTION 4

void send_rrq(int sockfd, const char *filename, const char *mode, struct sockaddr *server_addr, socklen_t server_len) {
    unsigned char rrq[512]; // Paquet de requête
    int len = 0;

    // Code de l'opération RRQ (2 octets)
    rrq[len++] = 0x00;
    rrq[len++] = 0x01; // RRQ

    // file name (ending by 0x00)
    strcpy((char *)&rrq[len], filename);
    len += strlen(filename) + 1;

    // Mode de transfert (terminé par 0x00)
    strcpy((char *)&rrq[len], mode);
    len += strlen(mode) + 1;

    // Envoi de la requête au serveur
    ssize_t sent_bytes = sendto(sockfd, rrq, len, 0, server_addr, server_len);
    if (sent_bytes == -1) {
        perror("Erreur d'envoi de la requête RRQ");
        exit(EXIT_FAILURE);
    }

     printf("Requête RRQ envoyée pour le fichier : %s\n", filename);
}