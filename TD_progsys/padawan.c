#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv[])
{
    pid_t ret;
    if(argc==1){
        printf("argc must be >1 \n");
        exit(EXIT_FAILURE);
    }
    printf("Yes my master : \n");
    for (int idx=0; idx<argv; idx++){
        printf("argv[%d] : %s\n", idx, argv[idx]);
    }
    execl(argv[1], argv[1], (char*)NULL);
    printf("Ne s'exécute jamais\n");

    exit(EXIT_SUCCESS);
}