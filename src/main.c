#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/sem.h>

int main(int argc, char **argv) {
    pid_t pid;
    int status, id;
    char *prog;
    struct sembuf wait_op = {0, -1, SEM_UNDO};
    union semun {
		int		val;
		struct semid_ds	*buf;
		unsigned short		*array;
	} semctl_arg;
    char *err_msg;
    key_t sem_key;

    if (argc == 1) {
        fprintf(stderr, "no executable provided\n");
        return 2;
    }
    prog = argv[1];
    sem_key = ftok(prog, 0);
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
    if ((pid = fork()) < 0) {
        err_msg = "fork";
        goto err;
    }
    if (pid == 0) {
        //According to C standard, argv[argc] is always NULL
        if (execvp(prog, &argv[1]) < 0) {
            err_msg = "exec";
            goto err;
        }
    }
    if (waitpid(pid, &status, 0) < 0) {
        err_msg = "wait";
        goto err;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 0;

 err:
    fprintf(stderr, "%s err\n", err_msg);
    return 1;
}
