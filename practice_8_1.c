#include<sys/types.h>
#include"ourhdr.h"
int glob=6;
char buf[]="a write to stdout\n";
int main(void){
    int var;
    pid_t pid;
    var=88;
    if(write(STDOUT_FILENO,buf,sizeof(buf)-1)==-1)
        err_sys("write error");
    printf("before vfork\n");
    int newfiledes;
    newfiledes=dup(STDOUT_FILENO);//copy the filedes

    if((pid=vfork())==-1) err_sys("vfork error");
    
    else if(pid==0){
        glob++;  
        var++;
        exit(0);
    }
    else{
        sleep(2);
    }
    char buf2[10];
    int pi=printf("pid=%d,glob=%d,var=%d\n",getpid(),glob,var);
    sprintf(buf2,"%d\n",pi); 
    write(newfiledes,buf2,strlen(buf));    
    exit(0);
}
