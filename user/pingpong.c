#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "common/common_def.h"


int main(int argc, char *argv[]) {
    
    int pid, childStatus;
    int fds[2];
    int MSGSIZE = 16;

    char inbuf[MSGSIZE];
    // printf("ping pong called\n");
    if(argc > 1){
        fprintf(STDERR_FD, "no arg expect");
        exit(1);
    }

    // pipe 要再fork之前创建 否则 子进程拿到的pipe和父进程拿到的pipe不是一个, 导致read假死
    if (pipe(fds) < 0)
        exit(1);
    
    pid = fork();
    if (pid == 0) {
        write(fds[1], "ping", MSGSIZE);
        printf("%d: received ping\n", getpid());
        // printf("ping pong fork called\n");

        // wait(&childStatus);
        exit(0);
    } else {
        wait(&childStatus);
        // printf("ping pong child exit %d called\n", childStatus);
        read(fds[0], inbuf, MSGSIZE);

        printf("%d: received pong\n", getpid());
    }

    exit(0);

}


