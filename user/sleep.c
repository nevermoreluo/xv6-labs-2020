#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include "common/common_def.h"

int main(int argc, char *argv[])
{
    int sleepTime, pid, childExit;
    char *time;

    if(argc <= 1){
        fprintf(STDERR_FD, "usage: sleep time \n");
        exit(1);
    }

    if (argc > 2) {
       fprintf(STDERR_FD, "too many args");
       exit(1);
    }
    
    time = argv[1];

    sleepTime = atoi(time);

    pid = fork();
    if (pid == 0) {
        sleep(sleepTime);
    } else {
        wait(&childExit);
        // printf("the child exited with status %d\n", childExit);
    }
    exit(0);
}

