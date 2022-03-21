#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
	pid_t filho;
	int status;
    for (int i= 1; i<=10; i++){
	    if (fork() == 0) {
	    	printf("\tpai: %d\n\tself: %d\n", getppid(), getpid());
	    	_exit(i);
	    } else {
	    	filho = wait(&status);
	    	printf("child: %d pid: %d\n",WEXITSTATUS(status), filho);
	    }
    }
	return 0;
}