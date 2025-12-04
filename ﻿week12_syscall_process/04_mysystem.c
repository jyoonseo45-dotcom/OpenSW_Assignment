#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int mysystem(const char *command) {
    pid_t pid;
    int status;

    if (command == NULL) {
        return 1;   // system(NULL)의 일반적 반환값
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return -1;
    }
    /* ---------------------------
       Child process
       조건 2: execl() ONLY 사용
       system()과 같은 기능:
       → /bin/sh -c <command>
    --------------------------- */
    else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);

        // exec 실패 시만 여기 도달
        perror("execl");
        exit(127);   // system()이 exec 실패 시 반환하는 표준 값
    }
    /* ---------------------------
       Parent process
       조건: child 종료까지 wait
    --------------------------- */
    else {
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return -1;
        }
        return status;   // system()도 wait()의 status 그대로 반환함
    }
}

int main(void) {

    mysystem("ls -l | wc -l");
    mysystem("find . -name \"*.c\"");

    printf("Good Bye~\n");

    return 0;
}
