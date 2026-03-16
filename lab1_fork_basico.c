
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

    pid_t pid = fork();

    if(pid < 0){
        perror("Error en fork");
        return 1;
    }
    else if(pid == 0){
        printf("Soy el proceso HIJO\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    }
    else{
        printf("Soy el proceso PADRE\n");
        printf("PID del padre: %d\n", getpid());
        printf("PID del hijo: %d\n", pid);
    }

    return 0;
}
