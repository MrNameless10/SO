/*

#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#define MAXBUFFER 1000

ssize_t readln(int fd, char *line, ssize_t size) {
	ssize_t res = 0;
	int j = 0;
	char local[MAXBUFFER];

	while ((res = read(fd, local, size)) > 0) {
		for(int i = 0; i < res; i++) {
			if ((char) local[i] != '\n') {
				line[j++] = local[i];
			} else return j;
		}
	}

	return j;
}

int numbers(char *buffer, int num) {
    char local[MAXBUFFER];
    int i=0, j=0;
    do {
        local[i++] = (num % 10) + 48;
        num/=10;
    } while (num != 0);
    while (i >= 0) {
        buffer[j++] = local[--i];
    }
    buffer[j++] = ' ';
    return j;
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		int linha = 1;
		int numSize, fd = open(argv[1], O_RDONLY);
		int endFile = lseek(fd,0,SEEK_END);
		lseek(fd, 0, SEEK_SET);
		char buffer[MAXBUFFER];
		char num[MAXBUFFER];
		ssize_t size, total = 0;

		while ((size = readln(fd, buffer, 100)) > 0 || total < endFile) {
			total += size;
			total++;
			if (size > 0) {
				numSize = numbers(num, linha++);
				write(1, "\t",1);
				write(1, num, numSize);
				write(1, buffer,size);
			}
			write(1, "\n",1);
			lseek(fd, total, SEEK_SET);
		}
		close(fd);
	}
	return 0;
}

*/

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NOME_SIZE 100

ssize_t read_segment(int fd, char *line, size_t size, char delimiter);
void insert_update(int db, char *name, char *age);

int main(int argc, char *argv[]) {
	int db, flag = 0;
	ssize_t n_read;
	char nome[NOME_SIZE];

	if (argc < 4)
		exit(EXIT_FAILURE);

	db = open("db.txt", O_CREAT | O_RDWR, 0600);

	switch (argv[1][1]) {
		case 'i':
			insert_update(db, argv[2], argv[3]);
			break;

		default:
			exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}


ssize_t read_segment(int fd, char *line, size_t size, char delimiter) {
	ssize_t n_read, res = 0;
	while ((n_read = read(fd, &line[res], 1)) > 0)
		if (line[res++] == delimiter)
			break;
	return res;
}

void insert_update(int db, char *name, char *age) {
	ssize_t n_read;
	char nome[NOME_SIZE];
	int flag = 0;

	while ((n_read = read_segment(db, nome, NOME_SIZE, ';')) > 0) {
		nome[n_read-1] = '\0';
		if (!strcmp(nome, name)) {
			flag = 1;
			break;
		}
		read_segment(db, nome, NOME_SIZE, '\n');
	}

	if (!flag) {
		write(db, name, strlen(name));
		write(db, ";", 1);
	}

	write(db, age, strlen(age));
	write(db, "\n", 1);
}
