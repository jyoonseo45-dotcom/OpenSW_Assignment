#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    /* ------------------------------
       조건 1, 2: 인자 검증 및 Usage 출력
       ./03_execve <program path> [OPTION...]
    ------------------------------- */
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program path> [OPTION...]\n", argv[0]);
        exit(1);
    }

    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    /* ------------------------------
       Child process
    ------------------------------ */
    else if (pid == 0) {

        // execve용 argv 구성: argv[1]부터 끝까지 그대로 전달
        // execv(path, args)
        char **new_argv = &argv[1];

        execv(argv[1], new_argv);

        // execv 실패 시 아래 코드 실행됨
        perror("execve");
        exit(1);   // 조건 4: 실패 시 code 1 반환
    }
    /* ------------------------------
       Parent process
    ------------------------------ */
    else {
        waitpid(pid, &status, 0);   // 조건 5

        if (WIFEXITED(status)) {
            printf("child exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("child did not exit normally.\n");
        }
    }
    if (argc < 2) {
    fprintf(stderr, "Usage: %s <program path> [OPTION...]\n", argv[0]);
    exit(1);
}

    return 0;
}
