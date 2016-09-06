#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char **argv) {
    int shmid = atoi(argv[1]);
    char *ptr;
    if ((ptr = shmat(shmid, 0, 0)) < 0) {
        fprintf(stderr, "shmat err\n");
        return 1;
    }
    int i = *(int *)ptr;
    printf("%d\n", i);
    return 0;
}
