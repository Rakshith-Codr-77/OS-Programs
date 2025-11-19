# Child–Parent Program

```c
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


# FCFS Scheduling

```c
#include<stdio.h>
int main()
{
    int bt[20], wt[20], tat[20], i, n;
    float wtavg, tatavg;

    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        printf("\nEnter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
    }

    wt[0] = wtavg = 0;
    tat[0] = tatavg = bt[0];

    for(i=1;i<n;i++)
    {
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = tat[i-1] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");

    for(i=0;i<n;i++)
        printf("\n\tP%d\t\t%d\t\t%d\t\t%d", i, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
}

# Round Robin Scheduling

```c
#include<stdio.h>
int main()
{
    int i, j, n, bu[10], wa[10], tat[10], t, ct[10], max;
    float awt = 0, att = 0, temp = 0;

    printf("Enter the no of processes -- ");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
        printf("\nEnter Burst Time for process %d -- ", i+1);
        scanf("%d", &bu[i]);
        ct[i] = bu[i];
    }

    printf("\nEnter the size of time slice -- ");
    scanf("%d", &t);

    max = bu[0];
    for(i=1;i<n;i++)
        if(max < bu[i])
            max = bu[i];

    for(j=0; j < (max/t) + 1; j++)
        for(i=0;i<n;i++)
            if(bu[i] != 0)
                if(bu[i] <= t)
                {
                    tat[i] = temp + bu[i];
                    temp += bu[i];
                    bu[i] = 0;
                }
                else
                {
                    bu[i] -= t;
                    temp += t;
                }

    for(i=0;i<n;i++)
    {
        wa[i] = tat[i] - ct[i];
        att += tat[i];
        awt += wa[i];
    }

    printf("\nThe Average Turnaround time is -- %f", att/n);
    printf("\nThe Average Waiting time is -- %f", awt/n);

    printf("\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");

    for(i=0;i<n;i++)
        printf("\t%d\t%d\t\t%d\t\t%d\n", i+1, ct[i], wa[i], tat[i]);
}

# Producer–Consumer

```c
#include<stdio.h>
#include<stdlib.h>

int mutex = 1;
int full = 0;
int empty = 3;
int x = 0;

void producer()
{
    --mutex;
    ++full;
    --empty;
    x++;
    printf("\nProducer produces item %d", x);
    ++mutex;
}

void consumer()
{
    --mutex;
    --full;
    ++empty;
    printf("\nConsumer consumes item %d", x);
    x--;
    ++mutex;
}

int main()
{
    int n;

    printf("\n1. Press 1 for Producer");
    printf("\n2. Press 2 for Consumer");
    printf("\n3. Press 3 for Exit");

    while(1)
    {
        printf("\nEnter your choice:");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                if((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is full!");
                break;

            case 2:
                if((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is empty!");
                break;

            case 3:
                exit(0);
        }
    }
}
