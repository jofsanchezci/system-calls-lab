
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid = fork();

    if(pid == 0){

        execlp("pwd","pwd",NULL);

    }
    else{

        wait(NULL);

        printf("PADRE: ejecución terminada\n");

    }

    return 0;
}
