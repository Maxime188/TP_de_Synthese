#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "variables.h"



int main(int argc, char* argv[]){

    char buffer[BUFSIZ];
    ssize_t byteRead; //read return 0 if it exists et -1 if it doesn't exist
    int status = 0;
    pid_t pid;


    while(strcmp(buffer,"exit")!=0){
        write(1,COMMAND, strlen(COMMAND));
    byteRead = read(0, buffer, sizeof(buffer)-1);

 
    buffer[byteRead - 1] = '\0'; //this lign is useful only in strcmp
    

    write(1,message, strlen(message));
    

        pid = fork();
        if (pid == 0) {
            char *args[] = {"/bin/sh", "-c", buffer, NULL};
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf(" [exit:%d] ", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf(" [sign:%d] ", WTERMSIG(status));
            }
        } else {
            perror("fork");
        }    

    }
     write(1,EXIT_MESSAGE, strlen(EXIT_MESSAGE));
    return 0;

    
}