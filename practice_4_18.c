#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include"ourhdr.h"
#define HOMEPATH "/home/xieyajin"
#define MAXDEPTH 100
#define DIRNAME "alonglonglonglonglonglonglonglonglonglongname"
int main(void)
{
    if(chdir(HOMEPATH)==-1)
        err_sys("initial chdir %s error",HOMEPATH);
    int i;
    for(i=0;i<MAXDEPTH;i++){
        if(mkdir(DIRNAME,DIR_MODE)==-1)
            err_sys("mkdir error at depth %d",i);
        if(chdir(DIRNAME)==-1)
            err_sys("chdir error at depth %d",i);
    }
    if(creat("depthfile",FILE_MODE)==-1)
        err_sys("creat file error");
    char *fullpath;
    int size;
    if((fullpath=path_alloc(&size))==NULL)
        err_sys("path_alloc error");
    for(; ; ){
        if(getcwd(fullpath,size)==NULL){
            printf("getcwd error,size=%d\n",size);
            size=size+100;
            if((fullpath=realloc(fullpath,size)==NULL))
                err_sys("realloc error");
        }
        else{
            break;
        }
    }
    
    printf("length of fullpath: %d",strlen(fullpath));
    exit(0);
}
