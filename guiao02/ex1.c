#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char* argv[]){
    printf("pid: %d\n", getpid());
    printf ("pai pid: %d\n", getppid());
    return 0;
}