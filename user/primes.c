#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "common/common_def.h"

#define SIZE 4

int isMod(int n, int p) {
    return n % p == 0;
}

void pipeline(int fd) {
    int childExit, n, p, pid, readO, nfd[2];
    pipe(nfd);
    
    readO = read(fd, &p, SIZE);
    // printf("read %d\n", p);
    if (readO == 0) {
        close(fd);
        exit(0);
    }
    printf("prime %d\n", p);

    pid = fork();
    if (pid == 0) {
        close(nfd[1]);
        pipeline(nfd[0]);
        // printf("pipeline fork end\n");    
        exit(0);
    } else {
        close(nfd[0]);
        while (read(fd, &n, SIZE) != 0) {
            if (isMod(n, p) == 0) {
                write(nfd[1], &n, SIZE);
            }
        }
        // 这个很关键原本以为不写入了对端read会返回0 其实不是，必须close后对端才会读到0
        close(nfd[1]);
        // printf("end pipeline\n");
        wait(&childExit);
        exit(0);
    }

}


int main(int argc, char *argv[]) {
    int limited = 35;
    int fd[2];

    pipe(fd);
    
    for (int i = 2; i <= limited; i++) {
        write(fd[1], &i, SIZE);
    }
    close(fd[1]);

    pipeline(fd[0]);

    exit(0);

    return 0;
}