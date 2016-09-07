#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

int main(int argc, char **argv) {
    int id = atoi(argv[1]);
    if (semctl(id, 0, IPC_RMID) < 0) {
        fprintf(stderr, "rm sem err\n");
        return 1;
    }
    return 0;
}
