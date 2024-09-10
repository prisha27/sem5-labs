#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "./my_rfifo"
#define BUFFER_SIZE 1024
#define NUM_WRITES 5

int main() {
    int pipe_fd;
    int res;
    char buffer[BUFFER_SIZE];
    int open_mode = O_WRONLY;

    if (access(FIFO_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_NAME, 0777) != 0) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    
    printf("Writer (PID %d) opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("Writer (PID %d) opened FIFO with fd %d\n", getpid(), pipe_fd);

    //write
    for (int i = 0; i < NUM_WRITES; i++) {
        printf(buffer, BUFFER_SIZE, "Message %d from writer", i);
        res = write(pipe_fd, buffer, strlen(buffer));
        if (res == -1) {
            perror("write");
            close(pipe_fd);
            exit(EXIT_FAILURE);
        }
        sleep(1); // Simulate time delay
    }

    
    close(pipe_fd);
    printf("Writer (PID %d) finished writing\n", getpid());
    exit(EXIT_SUCCESS);
}
