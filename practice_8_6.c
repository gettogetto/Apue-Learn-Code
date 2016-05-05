//#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    pid_t pid;
    if((pid=fork())<0){
        printf("fork() error\n");
        exit(0);
    }
    if(pid==0){
        exit(0);
    }
    sleep(2);
    system("ps -o pid,ppid,state,tty,command");
    exit(0);
}
