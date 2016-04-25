#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ourhdr.h"
char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";
int main(void){
    int fd;
    if( (fd=creat("file.hole",FILE_MODE)) <0){
        err_sys("create error");
    }
    if(write(fd,buf1,10) !=10){
        err_sys("buf1 write error");
    }
    if(lseek(fd,40,SEEK_SET) ==-1)
        err_sys("seek error");
    if(write(fd,buf2,10)!=10)
        err_sys("buf2 write error");
    exit(0);
}
