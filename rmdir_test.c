#include<unistd.h>
int main(int argc,char* argv[]){
    if(argc!=2){
        printf("argv!=2\n");
        exit(1);
    }
    if(rmdir(argv[1])==-1){//delete empty dir only
        printf("rmdir error\n"); 
        exit(1);
    }
    exit(0);
}
