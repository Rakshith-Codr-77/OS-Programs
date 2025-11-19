#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid;
    int status;

    printf("Parent Process Started (PID: %d)\n", getpid());
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("\n[Child] Child Process Created Successfully!\n");
        printf("[Child] Process ID (PID): %d\n", getpid());
        printf("[Child] Parent ID (PPID): %d\n", getppid());
        printf("[Child] Executing 'ls -l' command using exec()\n");

        execl("/bin/ls", "ls", "-l", NULL);

        perror("exec failed");
        exit(2);
    }
    else
    {
        printf("\n[Parent] Waiting for child process (PID: %d) to complete...\n", pid);
        wait(&status);

        printf("[Parent] Child process completed.\n");

        if (WIFEXITED(status))
            printf("[Parent] Child exited normally with status %d.\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("[Parent] Child terminated due to signal %d.\n", WTERMSIG(status));

        printf("[Parent] Parent process terminating.\n");
    }

    return 0;
}
