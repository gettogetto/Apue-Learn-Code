#include<stdio.h>
int main(){
    char *existpath="for_remove_test.txt";
    if(remove(existpath)==-1)//�����ļ���remove==ulink,����Ŀ¼remove==rmdir 
       printf("remove error\n");
    exit(0);
}
