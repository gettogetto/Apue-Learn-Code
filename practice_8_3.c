#include<sys/types.h>
#include"ourhdr.h"
static void charatatime(char *);
int main(void){
    pid_t pid;
    TELL_WAIT();
    if((pid=fork())<0){
        err_sys("fork error");
    }
    else if(pid==0){
        WAIT_PARENT();//父进程先执行
        charatatime("output from child\n");
        TELL_PARENT(getppid());//子进程完成告诉父进程
    }
    else {
        charatatime("output from parent\n");
        TELL_CHILD(pid);//父进程完成告诉子进程
        WAIT_CHILD();//等待子进程完成
    }    
    exit(0);
}
static void charatatime(char* str){
    char* ptr;
    int c;
    setbuf(stdout,NULL);//close buff
    for(ptr=str;c=*ptr++;) putc(c,stdout);
}
