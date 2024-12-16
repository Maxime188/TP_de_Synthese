#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "variables.h"
#include <time.h>




int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    ssize_t byteRead; //read return 0 if it exists et -1 if it doesn't exist
    int status = 0;
    pid_t pid;

    struct timespec start, end;
    


    while(strcmp(buffer,"exit")!=0){
        write(1,COMMAND, strlen(COMMAND));
    byteRead = read(0, buffer, sizeof(buffer)-1);

 
    buffer[byteRead - 1] = '\0'; //this lign is useful only in strcmp
    

    write(1,message, strlen(message));
    
        clock_gettime(CLOCK_MONOTONIC,&start);

        pid_t pid = fork();
        if(pid==0){
            // c'est le processus enfant
            char *args[] = {buffer,NULL};
            execvp(args[0],args); //on remplace la processus enfant par la commande 
            perror("Erreur d'exécution \n\r");
            exit(1);
        } else if (pid > 0) {
            waitpid(pid, &status, 0);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        long duree = (end.tv_sec - start.tv_sec) * 1000 
                 + (end.tv_nsec - start.tv_nsec) / 1000000;

        if(WIFEXITED(status)){
            int exitCode = WEXITSTATUS(status);
            char prompt[32];
            snprintf(prompt, sizeof(prompt), "[exit:%d|%ld ms]",exitCode,duree);
            write(1,prompt,strlen(prompt));


        } 
        else if(WIFSIGNALED(status)){
            int signalCode = WTERMSIG(status);
            char prompt[32];
            snprintf(prompt, sizeof(prompt), "[sign:%d|%ld ms]",signalCode, duree);
            write(1,prompt,strlen(prompt));

        }
        else {
        perror("Fork a rencotré un problème\n\r");
        }
    }


    write(1,EXIT_MESSAGE,strlen(EXIT_MESSAGE));
    return 0;  
}