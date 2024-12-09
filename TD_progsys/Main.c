#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
void print_PCB()
{
    pid_t pid = getpid();
    pid_t ppid = getpid();
    pid_t uid = getpid();
    pid_t gid = getpid();

    printf("Process Control Block (PCB) Information:\n");
    printf("PID (Process ID):%d\n", pid);
    printf("PPID (Parent Process ID):%d\n", ppid);
    printf("UID (User ID):%d\n", uid);
    printf("GID (Group ID): %d\n", gid);
}
int main()
{
pid_t ret = fork();
if (ret==0){
    printf("I'm the son and fork() has returned : %d\n", ret);
}
else{
    printf("I'm the father and fork() has returned : %d\n", ret);
}
printf("fork() has returned: %d\n", ret);
print_PCB();
exit(EXIT_SUCCESS);
}