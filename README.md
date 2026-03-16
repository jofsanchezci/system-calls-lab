
# Laboratorio: Procesos y Manejo de Archivos en C

## Sistemas Operativos

Este laboratorio permite practicar llamadas al sistema en Linux usando C:

- fork()
- exec()
- wait()
- open(), read(), write(), close()

## Compilación

gcc archivo.c -o programa

Ejemplo:

gcc lab1_fork_basico.c -o lab1
./lab1

## Estructura

system-calls-lab/
│
├── README.md
├── lab1_fork_basico.c
├── lab2_wait.c
├── lab3_exec.c
├── lab4_write_file.c
├── lab5_read_file.c
├── lab6_fork_file.c
└── lab7_fork_exec_wait.c

# Laboratorio: Procesos y Manejo de Archivos en C

## Sistemas Operativos

Este laboratorio tiene como objetivo que los estudiantes comprendan cómo interactúan los programas con el sistema operativo mediante **llamadas al sistema** en Linux.

Durante la práctica se utilizarán las siguientes llamadas al sistema:

* `fork()` — creación de procesos
* `exec()` — reemplazo del proceso
* `wait()` — sincronización entre procesos
* `open()`, `read()`, `write()`, `close()` — manejo de archivos

---

# Objetivos del laboratorio

Al finalizar el laboratorio el estudiante será capaz de:

* Comprender la relación entre **procesos padre e hijo**.
* Crear procesos utilizando `fork()`.
* Ejecutar programas externos con `exec()`.
* Sincronizar procesos usando `wait()`.
* Manipular archivos utilizando llamadas al sistema.
* Analizar el comportamiento de procesos concurrentes.

---

# Requisitos

Antes de iniciar el laboratorio el estudiante debe tener:

* Sistema operativo **Linux**
* Compilador **gcc**
* Conocimiento básico de **programación en C**
* Conocimiento básico de uso de **terminal**

---

# Estructura del repositorio

```
system-calls-lab/
│
├── README.md
│
├── lab1_fork_basico.c
├── lab2_wait.c
├── lab3_exec.c
├── lab4_write_file.c
├── lab5_read_file.c
├── lab6_fork_file.c
└── lab7_fork_exec_wait.c
```

---

# Compilación

Para compilar cualquier programa:

```bash
gcc nombre_programa.c -o programa
```

Ejemplo:

```bash
gcc lab1_fork_basico.c -o lab1
```

Ejecutar:

```bash
./lab1
```

---

# Actividad 1 — Creación de procesos con fork()

Archivo: **lab1_fork_basico.c**

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

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
```

### Preguntas

1. ¿Cuántos procesos se crean después de ejecutar el programa?
2. ¿Qué diferencia hay entre `getpid()` y `getppid()`?
3. ¿Por qué `fork()` devuelve valores diferentes?

---

# Actividad 2 — Sincronización con wait()

Archivo: **lab2_wait.c**

```c
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
```

### Preguntas

1. ¿Qué ocurre si eliminamos `wait()`?
2. ¿Qué representa el valor `5` retornado por el hijo?

---

# Actividad 3 — Ejecutar programas con exec()

Archivo: **lab3_exec.c**

```c
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
```

### Preguntas

1. ¿Qué ocurre con el código después de `exec()`?
2. ¿`exec()` crea un nuevo proceso?

---

# Actividad 4 — Escribir en un archivo

Archivo: **lab4_write_file.c**

```c
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
```

---

# Actividad 5 — Leer archivo

Archivo: **lab5_read_file.c**

```c
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
```

---

# Actividad 6 — fork() + archivos

Archivo: **lab6_fork_file.c**

El hijo escribe un archivo y el padre lo lee.

```c
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
```

---

# Actividad 7 — fork + exec + wait

Archivo: **lab7_fork_exec_wait.c**

```c
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
```

---

# Reto final

Desarrolle un programa que:

1. Cree un proceso hijo.
2. El hijo debe crear un archivo `reporte.txt`.
3. Debe escribir su PID en el archivo.
4. Debe ejecutar `cat reporte.txt`.
5. El padre debe esperar a que termine el hijo.

---

# Bibliografía

* Andrew Tanenbaum — *Modern Operating Systems*
* Silberschatz — *Operating System Concepts*
* Michael Kerrisk — *The Linux Programming Interface*

---

