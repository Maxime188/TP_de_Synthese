#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#include "variables.h"
#include <string.h>



int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    ssize_t byteRead; //read renvoie 0 si la chaîne existe et -1 si la chaîne n'existe pas


    while(strcmp(buffer,"exit")!=0){
        write(1,COMMAND, strlen(COMMAND));
    byteRead = read(0, buffer, sizeof(buffer)-1);

 
    buffer[byteRead - 1] = '\0'; //this lign is useful only in strcmp
    

    write(1,message, strlen(message));
 

    }
     write(1,EXIT_MESSAGE, strlen(EXIT_MESSAGE));
    return 0;

    
}