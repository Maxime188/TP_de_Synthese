#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>


#include "variables.h"
#include <time.h>

int main(int argc, char** argv){
    char buffer[128];
    int status;
    struct timespec start,end;

    ssize_t bytesRead;

    
    //Make a loop without condition to stop it
    while(strcmp(buffer,"exit")!=0){
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

        buffer[bytesRead-1] = '\0';

        clock_gettime(CLOCK_MONOTONIC, &start);

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
            snprintf(prompt, sizeof(prompt), "[exit:%d|%ld ms] %%",exitCode,duree);
            write(1,prompt,strlen(prompt));

        } else if(WIFSIGNALED(status)){
            int signalCode = WTERMSIG(status);
            char prompt[32];
            snprintf(prompt, sizeof(prompt), "[sign:%d|%ld ms] %%",signalCode,duree);
            write(1,prompt,strlen(prompt));
        }
    else {
        perror("Fork a rencotré un problème\n\r");
    }
}

    write(1,EXIT_MESSAGE,strlen(EXIT_MESSAGE));
    return 0;  

}
