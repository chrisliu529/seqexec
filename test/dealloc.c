#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

int main(int argc, char **argv) {
    int shmid = atoi(argv[1]);
    if (shmctl(shmid, IPC_RMID, 0) < 0) {
        fprintf(stderr, "dealloc err\n");
        return 1;
    }
    return 0;
}
