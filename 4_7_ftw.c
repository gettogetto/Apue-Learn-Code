#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<limits.h>
#include"ourhdr.h"

typedef int Myfunc(const char*,const struct stat*,int);

static Myfunc myfunc;
static int myftw(char*,Myfunc*);
static int dopath(Myfunc*);
static long nreg,ndir,nblk,nchr,nfifo,nslink,nsock,ntot;

int main(int argc,char* argv[])
{
    int ret;
    if(argc!=2) err_quit("argc!=2\n");
    ret=myftw(argv[1],myfunc);
    if((ntot=nreg+ndir+nblk+nfifo+nslink+nsock)==0)
        ntot=1;//防止分母为0
    printf("regular files  = %7ld, %5.2f %%\n", nreg,  nreg*100.0/ntot);
    printf("directories    = %7ld, %5.2f %%\n", ndir,  ndir*100.0/ntot);
    printf("block special  = %7ld, %5.2f %%\n", nblk,  nblk*100.0/ntot);
    printf("char special   = %7ld, %5.2f %%\n", nchr,  nchr*100.0/ntot);
    printf("FIFOs          = %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
    printf("symbolic links = %7ld, %5.2f %%\n", nslink,nslink*100.0/ntot);
    printf("sockets        = %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);

    exit(ret);
}
#define FTW_F 1         //file
#define FTW_D 2            //dir
#define FTW_DNR 3          //dir can not be read
#define FTW_NS 4           //file can not stat
static char *fullpath;
static int myftw(char *pathname,Myfunc *func)
{
    fullpath =path_alloc(NULL);/* malloc's for PATH_MAX+1 bytes */
    strcpy(fullpath,pathname);
    return dopath(func);
}
static int dopath(Myfunc* func)
{
    struct stat statbuf;
    struct dirent* dirp;
    DIR *dp;
    int ret;
    char *ptr;
    if(lstat(fullpath,&statbuf)<0)               /* stat error */
        return  func(fullpath,&statbuf,FTW_NS);//file can not stat
    if(S_ISDIR(statbuf.st_mode)==0)           /* not a directory */
        return func(fullpath,&statbuf,FTW_F);//file
    if((ret=func(fullpath,&statbuf,FTW_D))!=0)//dir
        return ret;
    ptr=fullpath+strlen(fullpath);      /* point to end of fullpath */
    *ptr++='/';
    *ptr=0;
    if((dp=opendir(fullpath))==NULL)    /* can't read directory */
        return func(fullpath,&statbuf,FTW_DNR); //dir can not be read
    while((dirp=readdir(dp))!=NULL)
    {
        if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
            continue;      /* ignore dot and dot-dot */
        strcpy(ptr,dirp->d_name);     /* append name after slash */
        if((ret=dopath(func))!=0)
            break;
    }
    ptr[-1]=0;     /* erase everything from slash onwards */
    if(closedir(dp)<0)
        err_ret("can not close dir %s",fullpath);
    return ret;
}
static int myfunc(const char* pathname,const struct stat* statptr,int type)
{
    switch(type)
    {
    case FTW_F:
        switch(statptr->st_mode&S_IFMT)//S_IFMT是一个掩码，它的值是017000（注意这里用的是八进制）， 可以用来过滤出前四位表示的文件类型。
            //通过掩码S_IFMT把其他无关的部分置0，再与表示目录的数值比较，从而判断类型
        case S_IFREG:
            nreg++;
            break;
        case S_IFBLK:
            nblk++;
            break;
        case S_IFCHR:
            nchr++;
            break;
        case S_IFIFO:
            nfifo++;
            break;
        case S_IFLNK:
            nslink++;
            break;
        case S_IFSOCK:
            nsock++;
            break;
        case S_IFDIR:
            err_dump("for S_IFDIR for %s",pathname);
        }
        break;
    case FTW_D:
        ndir++;
        break;
    case FTW_DNR:
        err_ret("can not read dir %s ",pathname);
    case FTW_NS:
        err_ret("stat error for %s",pathname);
    default:
        err_dump("unknown type %d for pathname",type,pathname);
    }
    return 0;
}




