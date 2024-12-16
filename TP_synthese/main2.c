#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if (argc !=3){
        fprintf(stderr, "Usage: %s <host> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *host=argv[1];
    char *file=argv[2];

    printf("Adresse du serveur : %s\n", host);
    printf("Nom du fichier : %s\n", file);

    struct addrinfo hints;
    struct addrinfo res;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;

    int en = getaddrinfo(host, "1069", &hints, &res&);
    if (en==1){
        perror("getaddrinfo");
        exite(EXIT_FAILURE);
    }

    return 0;

}