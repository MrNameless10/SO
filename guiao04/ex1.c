#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char const *argv[]){
    char buffer[1024];
    ssize_t line;

    int fi = dup(0);
    int fdi = open("/etc/passwd", O_RDONLY, 0666);
    int fdo = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    int fde = open("error.txt", O_CREAT| O_TRUNC | O_WRONLY, 0666);

    dup2(fdi,0);
    dup2(fdo,1);
    dup2(fde,2);

    close(fdi);
    close(fdo);
    close(fde);


    while(line = read(0, buffer, sizeof(buffer))){
        write(0, buffer, line);
        if (WEXITSTATUS(line) == 256 ){
            write(2, buffer, line);
        }
    }

    write(fi, "terminei\n", sizeof("terminei\n"));
    
    return 0;
}
