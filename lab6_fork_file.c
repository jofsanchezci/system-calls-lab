
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    pid_t pid = fork();

    if(pid == 0){

        int fd = open("proceso.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

        char msg[]="Mensaje generado por el proceso hijo\n";

        write(fd,msg,strlen(msg));

        close(fd);

    }
    else{

        wait(NULL);

        int fd = open("proceso.txt", O_RDONLY);

        char buffer[100];

        int n = read(fd, buffer, sizeof(buffer)-1);

        buffer[n]='\0';

        printf("PADRE lee:\n%s\n", buffer);

        close(fd);

    }

    return 0;
}
