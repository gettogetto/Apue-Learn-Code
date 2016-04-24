/*
实现dup2函数功能，不使用fcntl
dup2 equal to: close(newfd) ; fcntl(oldfd,F_DUPFD，newfd）；
如果newfd已经打开，则先将其关闭。如果newfd等于oldfd，则dup2返回newfd, 而不关闭它。dup2函数返回的新文件描述符同样与参数oldfd共享同一文件表项。

关键部分实现思路：
    先close关闭需要复制到的文件描述符newdup。
    连续dup,每dup一次产生的新的fd记录下来。
    当新产生的fd等于需要产生的fd的时候，跳出循环，并把前面产生的fd全都close掉，返回该描述符。

*/
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ourhdr.h"

int my_dup2(int oldfd,int newfd) {
	int tempfd;
	if((tempfd=dup(oldfd))==-1) { //判断原文件描述服是否有效
		printf("dup error\n");
		exit(1);
	} else
		close(tempfd);

	if(oldfd==newfd)//若新旧文件描述符相等则直接返回
		return newfd;

	close(newfd);//关闭要复制的文件描述符
	int fd_array[newfd];
	int i;
	for(i=0; i<newfd; i++) { //循环复制文件描述符
		fd_array[i]=0;
		tempfd=dup(newfd);
		if(tempfd==-1) {
			printf("dup error\n");
			exit(1);
		} else {
			if(tempfd==newfd) break;
			fd_array[i]=1;
		}
	}
	for(i=0; i<newfd; i++) { //关闭之前打开的非指定描述符
		if(fd_array[i]==1)
			close(i);
	}

	return tempfd;
}
int main(int argc,char* argv[]) {
	if(argc!=2) {
		printf("argc!=2\n");
		exit(1);
	}
	int fd;
	int newfd=3;
	if((fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE))==-1) {
		printf("open %s file error\n",argv[1]);
		exit(2);
	} else {
		newfd=my_dup2(fd,newfd);
	}
	if(write(newfd,"test my_dup2",strlen("test my_dup2"))==-1) {
		printf("write error\n");
		exit(3);
	} else {
		printf("write successfully\n");
	}
	exit(0);
}






