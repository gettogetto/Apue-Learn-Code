#include<sys/types.h>
#include<fcntl.h>
#include"ourhdr.h"
int main(int argc,char* argv[]){
    if(argc!=2)
        err_quit("error:argc!=2");
    if(access(argv[1],R_OK)==-1)//实际 用户id和组 id
        err_ret("access error for %s",argv[1]);
    else 
        printf("read access ok\n");
    if(open(argv[1],O_RDONLY)==-1)//有效用户id和组 id
        err_ret("open error for %s",argv[1]);
    else 
       printf("read open ok\n");
    exit(0);
}
