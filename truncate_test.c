#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
int main(){
    struct stat buf;
    stat("for_truncate_test.txt",&buf);
    printf("st_size: %d\n",buf.st_size);
    truncate("test.txt",5);//нд╪Ч╫ь╤л 
    stat("for_truncate_test.txt",&buf);
    printf("after truncate,st_size: %d\n",buf.st_size);
    exit(0);
}
