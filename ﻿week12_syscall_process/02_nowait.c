#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    /* -------------------------
       Child process
    -------------------------- */
    else if (pid == 0) {
        sleep(1);  // parent보다 늦게 종료
        printf("Child process PID: %d\n", getpid());
        printf("Child process PPID: %d\n", getppid());  // ★ parent 종료 후 PPID 변화 확인
        exit(7);
    }
    /* -------------------------
       Parent process
    -------------------------- */
    else {
        printf("Parent process PID: %d\n", getpid());
        printf("Parent process PPID: %d\n", getppid());

        // waitpid 없음 → 즉시 종료
        exit(0);
    }
}
