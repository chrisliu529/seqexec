#include <stdio.h>
#include <sys/shm.h>

int main() {
    int shmid;
    if ((shmid = shmget(IPC_PRIVATE, 16, 0600)) < 0) {
        fprintf(stderr, "shmget err\n");
        return 1;
    }
    printf("%d\n", shmid);
    return 0;
}
