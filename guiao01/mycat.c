#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include <stdio.h>


#define MAXBUFFER 1024

// Ex 1 -> mycat
int main(int argc, char *argv[]) {

	ssize_t res = 1;
	char buffer[MAXBUFFER];
	while(res != 0) {
		res = read(0, &buffer, MAXBUFFER);
		res = write(1, &buffer, res);
	}
	return 0;
}