#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"ourhdr.h"
int main(void){

    if(open("tempfile",O_CREAT|O_RDWR,FILE_MODE)<0)
        err_sys("open error");
    if(unlink("tempfile")<0)
        err_sys("unlink error\n");
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    exit(0);
}
