#include<sys/types.h>
#include<sys/wait.h>
#include"ourhdr.h"
int main(void){
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");
    while(fgets(buf,MAXLINE,stdin)!=NULL){
        buf[strlen(buf)-1]=0;
        if((pid=fork())<0)
            err_sys("fork error");
        else if(pid==0){
            execlp(buf,buf,(char*)0);
            err_ret("could not execute:%s",buf);
            exit(127);
        }
        if((pid=waitpid(pid,&status,0))<0)
            err_sys("waitpid error");
        printf("%% ");
    }
    exit(0);
}
