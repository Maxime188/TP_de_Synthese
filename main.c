#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "variables.h"

int main(int argc, char** argv){
    char buffer[128];
    char exit[] = "exit";

    ssize_t bytesRead;

    
    //Make a loop without condition to stop it
    while(1){
        //Entry Message
        write(1, ENTRY_MESSAGE, strlen(ENTRY_MESSAGE)-1);

        //Ask to write a command to the user
        write(1,ECRIRE_COMMANDE,strlen(ECRIRE_COMMANDE)-1);
        bytesRead = read(0, buffer, sizeof(buffer) - 1);  //On stock la commande écrite par user

        //Check if there is a problem after reading user prompt
        if (bytesRead < 0) {
        perror(ERREUR_LECTURE);
        return 1;
        }

        buffer[bytesRead] = '\0';

        //Si on écris 'exit' on quitte le shell (A FINIR CAR NE FONCTIONNE PAS ENCORE)
        if (buffer == exit){
        perror(ERREUR_LECTURE);
        return 1;
        }

    }
    return 0;  

}
