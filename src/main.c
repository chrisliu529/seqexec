#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/sem.h>

void usage() {
    printf("usage:\n"
    "seqexec --key=<string> prog [args...]\n");
}

int hash(char *str) {
    int h = 0;
    char *p = str;
    while (*p) {
        h = 31 * h + *p;
        p ++;
    }
    //normally, 24-bit is good enough
    return h & 0xffffff;
}

int parse_opts(int argc, char **argv, key_t *k) {
    if (argc < 3) {
        return 1;
    }
    if (strncmp(argv[1], "--key=", 6)) {
        return 1;
    }
    *k = (key_t)hash(&argv[1][6]);
    return 0;
}

int main(int argc, char **argv) {
    int id;
    char *prog;
    struct sembuf wait_op = {0, -1, SEM_UNDO};
    union semun {
		int		val;
		struct semid_ds	*buf;
		unsigned short		*array;
	} semctl_arg;
    char *err_msg;
    key_t sem_key;

    if (parse_opts(argc, argv, &sem_key)) {
        usage();
        return 2;
    }
    prog = argv[2];
    if ((id = semget(sem_key, 0, 0666)) < 0) {
        //initialize semaphore
        if ((id = semget(sem_key, 1, 0666 | IPC_CREAT)) < 0) {
            err_msg = "semget";
            goto err;
        }
        semctl_arg.val = 1;
        if (semctl(id, 0, SETVAL, semctl_arg) < 0) {
            err_msg = "sem setval";
            goto err;
        }
    }
    if (semop(id, &wait_op, 1) < 0) {
        err_msg = "semop";
        goto err;
    }
    return execvp(prog, &argv[2]);

 err:
    fprintf(stderr, "%s err\n", err_msg);
    return 1;
}
