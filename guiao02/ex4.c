#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	pid_t filho;
	int status;
    for (int i= 1; i<=10; i++){
	    if (fork() == 0) {
	    	printf("Filho %d:\n\tself: %d\n", i, getpid());
	    	_exit(i);
        }
    }
    for (int i=1; i<=10; i++){
        filho = wait(&status);
	    printf("Terminou child: %d pid: %d\n",WEXITSTATUS(status), filho);
	    
    }
    printf("Pai: %d\n", getpid());


	return 0;
}