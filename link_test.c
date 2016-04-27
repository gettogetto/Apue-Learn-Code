#include<sys/types.h>
#include<unistd.h>
int main(){
    char* newpath="newpath_link.txt";
    char* existpath="existpath_link.txt";
    if(link(existpath,newpath)==-1)//创建新的目录项newpath指向现存的文件的i节点 
        printf("link error\n");
    exit(0);

}
