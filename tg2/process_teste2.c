#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    /*int id = fork();

    if(id == 0){
        printf("Hello World from the child process\n");
    } else{
        printf("Hello World from the main process\n");
        fork();
    }
    
        
        printf("Hello World, from process = %d\n", id);
    
    wait(NULL);
    //exit(0);*/
    int pid, i;
    for( i = 0; i < 2; i++ ){
  
        pid=fork();
        if( pid == 0 ){

            printf("Sou o filho %d e tenho o pid %d\n", i, getpid());
        }
    }
    wait(NULL);
    printf("Acabou\n");

    return 0;
}