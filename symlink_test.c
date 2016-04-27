#include<unistd.h>
#include<stdio.h>
int main(){
    char* actualpath="for_symlink_test.txt";
    char* sympath="sympath.txt";
    if(symlink(actualpath,sympath)==-1)//创建指向actualpath的新目录项
        printf("symlink error\n");
    exit(0);
}
