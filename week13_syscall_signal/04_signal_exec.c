#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
    sigset_t block_set, pending_set;

    /* 1. SIGINT blocking 설정 */
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT);

    if (sigprocmask(SIG_BLOCK, &block_set, NULL) == -1) {
        perror("sigprocmask");
        exit(1);
    }

    printf("SIGINT blocked. Sleeping for 5 seconds...\n");
    printf("Try Ctrl + C during sleep.\n");

    /* 2. sleep(5) 동안 SIGINT를 보내볼 수 있음 */
    sleep(5);

    /* 3. pending 상태 확인 */
    sigemptyset(&pending_set);
    if (sigpending(&pending_set) == -1) {
        perror("sigpending");
        exit(1);
    }

    if (sigismember(&pending_set, SIGINT))
        printf("SIGINT is pending\n");
    else
        printf("SIGINT is not pending\n");

    return 0;
}
