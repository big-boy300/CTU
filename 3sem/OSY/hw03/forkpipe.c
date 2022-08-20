#define _POSIX_C_SOURCE 200112L

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define EXIT_RETVAL 2

bool volatile stopGen = false;

void handle_sigterm(int sig) {
    stopGen = true;
}

int main(int argc, char* argv[]) {
    int fd[2];

    if (pipe(fd) == -1) {
        exit(EXIT_RETVAL);
    }

    int pid1 = fork();
    if (pid1 == -1) {
        exit(EXIT_RETVAL);
    }

    if (pid1 == 0) {
        // GEN process
        if (close(fd[0]) == -1) {
            return EXIT_RETVAL;
        }

        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            return EXIT_RETVAL;
        }

        if (close(fd[1]) == -1) {
            return EXIT_RETVAL;
        }

        struct sigaction action;
        memset(&action, 0, sizeof(action));
        action.sa_handler = handle_sigterm;
        if (sigaction(SIGTERM, &action, NULL) == -1) {
            return EXIT_RETVAL;
        }
        while (!stopGen) {
            printf("%d %d\n", rand() % 4096, rand() % 4096);
            fflush(stdout);
            sleep(1);
        }
        fprintf(stderr, "GEN TERMINATED\n");
        return EXIT_SUCCESS;
    }

    int pid2 = fork();
    if (pid2 == -1) {
        exit(EXIT_RETVAL);
    }

    if (pid2 == 0) {
        // NSD process
        if (close(fd[1]) == -1) {
            return EXIT_RETVAL;
        }

        if (dup2(fd[0], STDIN_FILENO) == -1) {
            return EXIT_RETVAL;
        }

        if (close(fd[0]) == -1) {
            return EXIT_RETVAL;
        }

        if (execl("nsd", "nsd", NULL) == -1) {
            return EXIT_RETVAL;
        }
    }

    // MAIN process
    if (close(fd[0]) == -1) {
        exit(EXIT_RETVAL);
    }

    if (close(fd[1]) == -1) {
        exit(EXIT_RETVAL);
    }

    sleep(5);

    if (kill(pid1, SIGTERM) == -1) {
        exit(EXIT_RETVAL);
    }

    int pid1Status;
    if (waitpid(pid1, &pid1Status, 0) == -1) {
        exit(EXIT_RETVAL);
    }
    int pid1ExitValue = WEXITSTATUS(pid1Status);

    int pid2Status;
    if (waitpid(pid2, &pid2Status, 0) == -1) {
        exit(EXIT_RETVAL);
    }
    int pid2ExitValue = WEXITSTATUS(pid2Status);

    if (pid1ExitValue == 2 || pid2ExitValue == 2) {
        printf("ERROR\n");
        return EXIT_FAILURE;
    } else {
        printf("OK\n");
        return EXIT_SUCCESS;
    }
}
