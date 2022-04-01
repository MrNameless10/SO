#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    pid_t filho;
    int status;

    if (fork() == 0){
        execlp("ls", "ls", "-l", NULL);
    } else {
        filho = wait(&status);
        if(WEXITSTATUS(status) == 255)
			printf("[process %d]: ERROR!\n", filho);
		else 
			printf("[process %d]: Works!\n", filho);
    }

    return 0;
}