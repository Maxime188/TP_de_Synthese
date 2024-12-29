#include <stdio.h>
#include <string.h>
#include "gettftp.h"
#include "puttftp.h"

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

    
}