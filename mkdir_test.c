#include<sys/stat.h>
#include<sys/types.h>
int main(int argc,char* argv[]){
    if(argc!=2){
        printf("argc!=2\n");
        exit(1);  
    }
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    if(mkdir(argv[1],mode)==-1){
        printf("mkdir error\n");
        exit(1);
    }
    exit(0);
}
