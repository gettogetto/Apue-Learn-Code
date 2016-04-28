#include <fcntl.h>
#include "ourhdr.h"
void setfl(int fd,int flags){
    int val;
    if( (val=fcntl(fd,F_GETFL,0))<0)
        err_sys("fcntl F_GETFL error");
    val|=flags;
    if(fcntl(fd,F_SETFL,val)<0)//当仅知道打开文件的描述符时可以修改其性质
        err_sys("fcntl F_SETFL error");
}
void clrfl(int fd,int flags){
    int val;
    if( (val=fcntl(fd,F_GETFL,0))<0)
        err_sys("fcntl F_GETFL error");
    val&=~flags;
    if(fcntl(fd,F_SETFL,val)<0)
        err_sys("fcntl F_SETFL error");
}

#define BUFFSIZE 8192
int main(void){
    setfl(STDOUT_FILENO,O_SYNC);//同步写,每次write都要等待数据写入磁盘再返回，而通常write只是将数据
    //排入队列，实际io则等到以后某个时刻进行
    int n;
    char buf[BUFFSIZE];
    while( (n=read(STDIN_FILENO,buf,BUFFSIZE)) >0){
        if( write(STDOUT_FILENO,buf,n) != n)
            err_sys("write error");
    }
    if( n<0)
        err_sys("read_error");
    exit(0);
}

