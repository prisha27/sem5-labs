#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;
    int n;
    char *msg;

    
    pid = fork();

    if (pid < 0) {
        // Fork failed
        printf("fork");
        
    } else if (pid == 0) {
        // This is the child process
       msg="child";
        n=5;
        sleep(3); // Simulate some work with a sleep
        
    } else {
        // This is the parent process
        msg="parent";
        n=2;
        // Wait for the child process to complete
        pid_t terminated_pid = wait(&status);
        
        if (terminated_pid == -1) {
            // Error occurred during wait
            printf("wait");

        }
        }

for(;n>0;n--)
{
puts(msg);
}
        return 0;
        }
