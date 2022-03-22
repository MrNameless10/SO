#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#define NUM_LINHAS 10
#define NUM_COLS 50
/*
##################
# Dynamic Matrix #
##################

//usar a função waitpid 


int main(int argc, char *argv[]){
	srand(atoi(argv[2]));
	int linhas = rand()%10 +1;		   // número random entre 1 e 10
	int colunas = rand()%20;   // número random entre 10 e 29
	int matriz[linhas][colunas];
	
	int size;
	char buffer[128];

	size = snprintf(buffer, 128,"Matriz %d por %d\n", linhas, colunas);
	write(1, buffer, size);


	// preencher a matriz random
	for(int i=0; i<linhas; i+=1){
		for(int j=0; j<colunas; j+=1){
			matriz[i][j] = rand()%10;
			printf("%d   ", matriz[i][j]);
		}
		printf("\n");

	}

	int findMe = atoi(argv[1]);
	int status;
	pid_t pid;
	pid_t array_de_pids[10];
	
	// procurar o número na matriz
	for(int i=0; i<linhas; i++){
		if((pid = fork()) == 0){
			for(int j=0; j<colunas; j++){
				if(matriz[i][j] == findMe){
					_exit(i);
				}
			}
				
			_exit(-1);
		} else {
			array_de_pids[i] = pid;
		}
	}



	for(int i = 0; i<linhas; i++){
		pid = wait(&status);
		if(WEXITSTATUS(status) == 255) // quando dá return -1
			printf("[Process: %d] Não encontrei nada\n", pid);
		else{
			printf("[Process: %d] Encontrei o numero %d na linha %d\n", pid, findMe, WEXITSTATUS(status));
		}
	}

	return 0;
}
*/




/*
###################
# Static Solution #
###################
*/
int main() {
	pid_t filho, pid;
    int matriz[10][50];
    int needle = 20;
	int status;
    int pids[NUM_LINHAS];

    for (int i= 0; i<NUM_LINHAS; i++){
	    if (pid = fork() == 0) {
            printf("[pid %d] row: %d\n",getpid(),i);

            //Start searching for the given number in row #1
            for(int j = 0; j<NUM_COLS; j++)
                if (matriz[i][j] == needle) 
                    _exit(i);
	    	_exit(-1);
    
        } else{
            pids[i] = pid;
        }
    }
    
    for (int i=0; i<NUM_LINHAS; i++){
        filho = waitpid(pids[i], &status, 0);
        if(WIFEXITED(status)){
            if(WEXITSTATUS(status) < 255)
                printf("[pai] process %d exited. found number at row: %d\n", filho, WEXITSTATUS(status));
            else 
                printf("[pai] process %d exited. nothing found\n", filho);
        }else
            printf("[pai] process %d exited. Something went wrong\n", filho);   
    }


	return 0;
}