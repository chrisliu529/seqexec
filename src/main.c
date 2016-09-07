#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    pid_t pid;
    int status;
    if (argc == 1) {
        printf("no executable provided\n");
        return 2;
    }
    if ((pid = fork()) < 0) {
        fprintf(stderr, "fork err\n");
        return 1;
    }
    if (pid == 0) {
        //According to C standard, argv[argc] is always NULL
        if (execvp(argv[1], &argv[1]) < 0) {
            fprintf(stderr, "exec err\n");
            return 1;
        }
    }
    if (waitpid(pid, &status, 0) < 0) {
        fprintf(stderr, "wait err\n");
        return 1;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 0;
}
