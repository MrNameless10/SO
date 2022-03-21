/*
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include <stdio.h>

#define MAXBUFFER 1

#define MAX_READ_BUFFER 2
char read_buffer[MAX_READ_BUFFER];
char 
*/
/*
ssize_t readln(int fd, char *line, ssize_t size) {
	int i = 0;
    while( i < size && readc (fd, &buf[i]) > 0){
        i++;
        if ((char*) buf)[i-1] == '\n'{ // cast que serve só para garantir que o buffer é deste tipo
            return i;
        }
    }
return i;

*/

/* resolução
ssize_t readln(int fd, char *line, ssize_t size) {
	ssize_t res = 0;
	ssize_t i = 0;
	while ((res = read(fd, &line[i], size)) > 0 && ((char) line[i] != '\n')) {
		i+=res;
	}
return i;
*/
/*

int readc(int fd, char * c){
    if(read_buffer_pos == read_buffer_end){
        read_buffer
    }
}


int main(int argc, char *argv[]) {
	char line[100];
	ssize_t size;
	if (argc < 2) return -1;

	int fd = open(argv[1], O_RDONLY);
	ssize_t tam = (ssize_t) atoi(argv[2]);

	size = readln(fd, line, tam);

	write(1, &line, size);
	line[0] = '\n';
	write(1, line, 1);
	close(fd);
	return 0;
}
*/

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

ssize_t readln(int fd, char *line, size_t size) {
	ssize_t res = 0;
	ssize_t i = 0;

	while ((res = read(fd, &line[i], size)) != 0 && ((char) line[i-1] != '\n'))
		i += res;

	return i;
}

int main(int argc, char *argv[]) {
	char line[100];
	ssize_t size;

	if (argc != 3)
		exit(EXIT_FAILURE);

	int fd = open(argv[1], O_RDONLY);
	ssize_t tam = (ssize_t) atoi(argv[2]);

	size = readln(fd, line, tam);
	write(STDIN_FILENO, &line, size);
	close(fd);

	return EXIT_SUCCESS;
}