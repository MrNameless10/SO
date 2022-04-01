#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	pid_t filho;
	int status;


	for(int i=1; i<argc; i+=1){
		if( (fork()) == 0){
			execlp(argv[i], argv[i], NULL);
			_exit(-1);
		}
	}

	for(int i=1; i<argc; i+=1){
		filho = wait(&status);
		if(WEXITSTATUS(status) == 255)
			printf("[process %d]: ERROR!\n", filho);
		else
			printf("[process %d]: Works!\n", filho);

	}


	return 0;
}