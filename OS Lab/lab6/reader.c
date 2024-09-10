#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "./my_rfifo"
#define BUFFER_SIZE 1024

int main() {
    int pipe_fd;
    int res;
    char buffer[BUFFER_SIZE+1];
    int open_mode = O_RDONLY;

    
    printf("Reader (PID %d) opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    printf("Reader (PID %d) opened FIFO with fd %d\n", getpid(), pipe_fd);

    // read
    while ((res = read(pipe_fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[res] = '\0'; // Null-terminate the string
        printf("Reader (PID %d) received: %s\n", getpid(), buffer);
    }

    if (res == -1) {
        perror("read");
        close(pipe_fd);
        exit(EXIT_FAILURE);
    }

    // close
    close(pipe_fd);
    printf("Reader (PID %d) finished reading\n", getpid());
    exit(EXIT_SUCCESS);
}
