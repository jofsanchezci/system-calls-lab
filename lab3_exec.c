
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid = fork();

    if(pid == 0){

        printf("HIJO: ejecutando comando ls\n");

        execlp("ls","ls","-l",NULL);

        perror("Error en exec");

    }
    else{

        wait(NULL);

        printf("PADRE: el hijo terminó\n");

    }

    return 0;
}
