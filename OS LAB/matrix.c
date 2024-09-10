#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

void printmatrix(int matrix[3][3]) {
    
    for(int i=0;i<3;i++)
    {
    	for(int j=0;j<3;j++)
    	{
    		printf("%d ",matrix[i][j]);
    	}
    	printf("\n");
    }
}

void incre(int matrix[3][3])
{

    for(int i=0;i<3;i++)
    {
    	for(int j=0;j<3;j++)
    	{
    		matrix[i][j]++;
    	}
    }

}
int main() {
    int fd[2];

    int a[3][3]={{1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    if (pipe(fd) == -1) {
        perror("pipe");
        }
    
    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        
    }

    if (pid == 0) {
        
        close(fd[1]);
        int cm[3][3];

        read(fd[0],cm,sizeof(cm));

        printf("child matrix \n");
        incre(cm);
        printmatrix(cm);

        close(fd[0]);
       
       
    } else {
        
        close(fd[0]); 
        write(fd[1],a,sizeof(a));
        printf("parent matrix \n");
        printmatrix(a);
      close(fd[1]);
      wait(NULL);
        
    }
}