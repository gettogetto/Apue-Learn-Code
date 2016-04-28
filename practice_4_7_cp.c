#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include"ourhdr.h"

#define BUFFSIZE 8192
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        printf("error:argc should be 3\n");
        exit(1);
    }

    char buff[BUFFSIZE];
    int fd;
    if((fd=open(argv[1],O_RDONLY,FILE_MODE))==-1)
    {
        err_sys("open error\n");
    }
    int fdc;
    if((fdc=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE))==-1)
    {
        err_sys("creat error\n");
    }
    int n;
    while((n=read(fd,buff,BUFFSIZE))>0)
    {
        char buffout[BUFFSIZE];
        int k;
        int index=0;
        for(k=0;k<BUFFSIZE;k++){
            if(buff[k]!='\0') buffout[index++]=buff[k];
        }
        n=index;
        if(write(fdc,buffout,n)!=n)
        {
            err_sys("write error\n");
        }
    }
    if(n<0) err_sys("read error\n");
    close(fd);
    close(fdc);
    exit(0);
}
