#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_FIB 100

// Function to generate Fibonacci series and write to the pipe
void producer(int write_fd) {
    int a = 0, b = 1, next;
    for (int i = 0; i < 10; ++i) {
        // Calculate next Fibonacci number
        if (i == 0) next = a;
        else if (i == 1) next = b;
        else {
            next = a + b;
            a = b;
            b = next;
        }
        
        // Write Fibonacci number to the pipe
        if (write(write_fd, &next, sizeof(next)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        sleep(1); // Sleep to simulate work and allow consumer to read
    }
    
    // Close the write end of the pipe
    close(write_fd);
}

// Function to read from the pipe and print Fibonacci numbers
void consumer(int read_fd) {
    int num;
    while (read(read_fd, &num, sizeof(num)) > 0) {
        printf("Consumed Fibonacci number: %d\n", num);
    }
    
    // Close the read end of the pipe
    close(read_fd);
}

int main() {
    int pipe_fd[2];
    
    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    // Fork the process to create a child
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: Consumer
        close(pipe_fd[1]); // Close unused write end
        consumer(pipe_fd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process: Producer
        close(pipe_fd[0]); // Close unused read end
        producer(pipe_fd[1]);
        
        // Wait for the child process to complete
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}
