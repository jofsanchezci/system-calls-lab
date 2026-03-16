
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

    int fd;

    char mensaje[]="Hola desde el sistema operativo\n";

    fd = open("salida.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if(fd < 0){
        perror("Error al abrir archivo");
        return 1;
    }

    write(fd, mensaje, strlen(mensaje));

    close(fd);

    printf("Archivo creado correctamente\n");

    return 0;
}
