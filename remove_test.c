#include<stdio.h>
int main(){
    char *existpath="for_remove_test.txt";
    if(remove(existpath)==-1)//对于文件，remove==ulink,对于目录remove==rmdir 
       printf("remove error\n");
    exit(0);
}
