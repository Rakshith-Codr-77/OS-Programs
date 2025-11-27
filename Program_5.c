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
