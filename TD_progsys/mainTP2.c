#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    struct stat sb;
    if (stat(argv[1], &sb)==-1){
        perror("stat");
        exit(EXIT_FAILURE);
    }
    else{
        printf(argv[1], sb.st_blksize);
        //exit(EXIT_SUCCESS);
    }
}