#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char **argv) {
        if (argc < 2) exit(0);

        signal(SIGCHLD, SIG_IGN);
        signal(SIGHUP, SIG_IGN);

        char *cmd, *ptr = cmd = calloc(sizeof(char), 8192);
        int i;
        for (i = 1; i < argc; i++) {
                char *aptr = argv[i];
                while (*aptr != '\0')
                        *ptr++ = *aptr++;
                *ptr++ = ' ';
        }

        int pid = fork();
        if (pid != 0) {
                sleep(1);
                kill(pid, SIGKILL);
                exit(0);
        }
        setsid();
        system(cmd);
        free(cmd);
        return 0;
}
