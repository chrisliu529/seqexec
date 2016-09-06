#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char **argv) {
    int shmid = atoi(argv[1]);
    char *ptr;
    int i, j;
    if ((ptr = shmat(shmid, 0, 0)) < 0) {
        fprintf(stderr, "shmat err\n");
        return 1;
    }
    int times = atoi(argv[2]);
    for (i = 0; i < times; i ++) {
        j = *(int *)ptr;
        *(int *)ptr = ++j;
    }
    return 0;
}
