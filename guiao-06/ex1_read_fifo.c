#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX_LINE_SIZE 1024  


int main() {
    int fd;
    int bytes_read;
    ssize_t n_read;

    int fifo = open("fifo", O_RDONLY);

    while (n_read = read(fifo, buffer, sizeof(buffer))) {
        write(STDOUT_FILENO, buffer, n_read);
    }

    return 0;
}