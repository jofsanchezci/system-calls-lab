
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid = fork();

    if(pid == 0){
        printf("HIJO: ejecutándose...\n");
        sleep(3);
        printf("HIJO: terminando\n");
        return 5;
    }
    else{

        int status;

        printf("PADRE: esperando al hijo\n");

        wait(&status);

        printf("PADRE: el hijo terminó\n");

        if(WIFEXITED(status)){
            printf("Código de salida del hijo: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
