#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    /* -------------------------
       Child process
    -------------------------- */
    else if (pid == 0) {
        printf("Child process PID: %d\n", getpid());
        printf("Child process PPID: %d\n", getppid());

        exit(7);   // 조건 2: child process는 종료 시 7 반환
    }
    /* -------------------------
       Parent process
    -------------------------- */
    else {
        printf("Parent process PID: %d\n", getpid());
        printf("Parent process PPID: %d\n", getppid());

        // 조건 3: child 종료까지 기다림
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
