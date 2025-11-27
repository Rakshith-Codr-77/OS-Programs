# OS-PROGRAMS

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
```

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
```

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
```

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
```
# Program 4  
## Writer Process

```c
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd;
    char buf[1024] = "Hello RNSIT";
    char *myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    printf("Run Reader process to read the FIFO file\n");

    fd = open(myfifo, O_WRONLY);
    write(fd, buf, sizeof(buf));
    close(fd);

    unlink(myfifo);

    return 0;
}
```
## Reader Process
```c
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 1024

int main() {
    int fd;
    char *myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Reader process has read: %s\n", buf);
    close(fd);

    return 0;
}
```
# Program 5

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int f[50], p, i, st, len, j, c, k, a, fn = 0;

    for (i = 0; i < 50; i++)
        f[i] = 0;

x:
    fn = fn + 1;
    printf("Enter index starting block and length: ");
    scanf("%d%d", &st, &len);
    k = len;

    if (f[st] == 0) {
        for (j = st; j < (st + k); j++) {
            if (f[j] == 0) {
                f[j] = fn;
                printf("%d-------->%d\n", j, f[j]);
            } else {
                printf("%d Block is already allocated\n", j);
                k++;
            }
        }
    } else {
        printf("%d starting block is already allocated\n", st);
    }

    printf("Do you want to enter more file (Yes-1 / No-0): ");
    scanf("%d", &c);

    if (c == 1)
        goto x;
    else
        exit(0);

    return 0;
}
```
# Program 6

```c
#include <stdio.h>

int main() {
    int t[20], d[20], h, i, j, n, temp, k, atr[20], p, sum = 0;

    printf("enter the no of tracks to be traversed: ");
    scanf("%d", &n);

    printf("enter the position of head: ");
    scanf("%d", &h);

    t[0] = 0;
    t[1] = h;

    printf("enter the tracks: ");
    for (i = 2; i < n + 2; i++)
        scanf("%d", &t[i]);

    for (i = 0; i < n + 2; i++) {
        for (j = 0; j < (n + 2) - i - 1; j++) {
            if (t[j] > t[j + 1]) {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n + 2; i++)
        if (t[i] == h) {
            j = i;
            k = i;
            p = 0;
        }

    while (t[j] != 0) {
        atr[p] = t[j];
        j--;
        p++;
    }

    atr[p] = t[j];

    for (p = k + 1; p < n + 2; p++, k++)
        atr[p] = t[k + 1];

    printf("seek sequence is:");
    for (j = 0; j < n + 1; j++) {
        if (atr[j] > atr[j + 1])
            d[j] = atr[j] - atr[j + 1];
        else
            d[j] = atr[j + 1] - atr[j];
        sum += d[j];
        printf("\n%d", atr[j]);
    }

    printf("\nTotal head movements: %d", sum);
    return 0;
}
```
