#include<sys/types.h>
#include<unistd.h>
int main(){
    char* newpath="newpath_link.txt";
    char* existpath="existpath_link.txt";
    if(link(existpath,newpath)==-1)//�����µ�Ŀ¼��newpathָ���ִ���ļ���i�ڵ� 
        printf("link error\n");
    exit(0);

}
