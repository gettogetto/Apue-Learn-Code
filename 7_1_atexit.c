#include"ourhdr.h"
static void exit1(void),exit2(void);
int main(void){
    if((atexit(exit2))!=0) err_sys("atexit exit1 error");
    if((atexit(exit1))!=0) err_sys("atexit exit2 error");
    if((atexit(exit1))!=0) err_sys("atexit exit2 error");
    exit(0);
}
void exit1(void){
    printf("exit1\n");
}
void exit2(void){
    printf("exit2\n");
}
