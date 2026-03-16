
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    int fd;

    char buffer[100];

    fd = open("salida.txt", O_RDONLY);

    int n = read(fd, buffer, sizeof(buffer)-1);

    buffer[n] = '\0';

    printf("Contenido:\n%s\n", buffer);

    close(fd);

    return 0;
}
