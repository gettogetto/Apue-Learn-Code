#include<dirent.h> /*opendir()*/
#include<unistd.h> /*execl(),fcntl()*/
#include<fcntl.h>
 /*一些必要的头文件*/

int main(void)
{
    DIR *dir;
    pid_t pid;
    int val, fd;
    char buf[10]; /*for save fd*/

    dir = opendir("/");
    fd = dirfd(dir);

    if((val = fcntl(fd,F_GETFD,0)) < 0)
        perror("fcntl");
    if(val & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");
     
    //val &= ~FD_CLOEXEC;//to set close on exec dff
    //fcntl(fd,F_SETFD,val);
    sprintf(buf,"%d\0",fd);

    if((pid = fork()) < 0)
        perror("fork");
    else if(pid == 0)
    {
        execl("/home/xieyajin/apueDir/apue/file/practice_8_7_child","practice_8_7_child",buf,NULL);
        exit(0);
    }

    return 0;
}
