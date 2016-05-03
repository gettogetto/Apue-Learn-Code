#include "ourhdr.h"
int main(void){
    int c;
    while((c=fgetc(stdin))!=EOF){//or replace by getc and putc
        if(fputc(c,stdout)==EOF){
            err_sys("putc error");
         }
    }
    if(ferror(stdin)){
        err_sys("input error");
    }
    exit(0);
}
