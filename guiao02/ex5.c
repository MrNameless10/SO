#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define NUM_LINHAS 10
#define NUM_COLS 50

/*

int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Usage : program <needle>\n");
        exit(-1);
    }

    pid_t pid;
    int needle = atoi(argv[1]);
    int rows = 10;
    int cols = 10000;
    int rand_max = 10000;
    int status;
    int **matrix;

    //
    printf("Generating numbers from 0 to %d...", rand_max);
    matrix = (int **) malloc(sizeof(int*)) * rows);

}
*/
/*
###################
# Static Solution #
###################
*/
int main() {
	pid_t filho;
    int matriz[10][50];
    int needle = 20;
	int status;

    for (int i= 0; i<NUM_LINHAS; i++){
	    if (fork() == 0) {
            printf("[pid %d] row: %d\n",getpid(),i);

            //Start searching for the given number in row #1
            for(int j = 0; j<NUM_COLS; j++)
                if (matriz[i][j] == needle) 
                    _exit(i);
	    	_exit(-1);
        }
    }
    
    for (int i=0; i<NUM_LINHAS; i++){
        filho = wait(&status);
        if(WIFEXITED(status)){
            //8 bits
            if(WEXITSTATUS(status)<255)
                printf("[pai] process %d exited. found number at row: %d\n", filho, WEXITSTATUS(status));
            else 
                printf("[pai] process %d exited. nothing found\n", filho);
        }else
            printf("[pai] process %d exited. Something went wrong\n", filho);   
    }


	return 0;
}