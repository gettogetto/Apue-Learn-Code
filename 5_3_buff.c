#include"ourhdr.h"
void pr_stdio(const char* ,FILE* );
int main(void){
    FILE* fp;
    fputs("enter any chartacter\n",stdout);
    if(getc(stdin)==EOF) err_sys("getchar error");
    fputs("one line to stderr\n",stderr);
    pr_stdio("stdin",stdin);
    pr_stdio("stdout",stdout);
    pr_stdio("stderr",stderr);
    if( (fp=fopen("1_1.c","r"))==NULL)
        err_sys("fopen error");
    if(getc(fp)==EOF)
        err_sys("getc error");
    pr_stdio("1_1.c",fp);
    exit(0);
}
void pr_stdio(const char* name,FILE* fp){
    printf("stream= %s  ",name);
    if(fp->_flags&_IONBF) printf("unbuffered\n");
    else if(fp->_flags&_IOLBF) printf("linebuffered\n");
    else printf("fully buffered\n");
   // printf("buffer size:%d",fp->_bufsiz);
}
