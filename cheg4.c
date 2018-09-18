#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
char *
getinput(char *buffer, size_t buflen) {
        printf("$$ ");
        return fgets(buffer, buflen, stdin);
}
int
main(int argc, char **argv) {
        char buf[1024];
        pid_t pid;
        int status;
        int fds[2];
        int child[2];
        char *argv[3];
        pipe(fds);
        while (getinput(buf, sizeof(buf))) {
               buf[strlen(buf) - 1] = '\0';
               if((pid=fork()) == -1) {
                       fprintf(stderr, "shell: can't fork: %s\n",
                                      strerror(errno));
                       continue;
               } else if (pid == 0) {  
                       /* child to run the command */
                       /* your code to parse the command & set any file redirection as needed */     
                       execlp(buf, buf, (char *)0);
                       fprintf(stderr, "shell: couldn't exec %s: %s\n", buf,
                                      strerror(errno));
                       exit(EX_DATAERR);
               }
               if (fork()== 0)
{
    close(fds[1]);
    close(STDIN_FILENO); dup(fds[0]);
          /* redirect standard input to fds[0] */
    argv[0] = "/bin/more";
    argv[1] = NULL;          
    execv(argv[0], argv);
    exit(-1);
}
if (fork() == 0)
{
    close(fds[0]);
    close(STDOUT_FILENO); dup(fds[1]);
    argv[0] = "/bin/ps";
    argv[1] = "-ef"; argv[2] = NULL;
    execv(argv[0], argv);
    exit(-2);
}
close(fds[0]); close(fds[1]);
wait(child);
wait(child+1);
}
            // parent is waiting
               if ((pid=waitpid(pid, &status, 0)) < 0)
                       fprintf(stderr, "shell: waitpid error: %s\n",
                                      strerror(errno));
        }
        exit(EX_OK);
}