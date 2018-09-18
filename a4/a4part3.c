#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

static char* args[512];
pid_t pid;
int command_pipe[2];
static void waiting(int n);

static int command(int input, int first, int last)
{
   int fd[2];
    int flag=0;
   pipe( fd );  
   pid = fork();

    if (pid == 0) {
       for(int i=0;args[i]!=0;i++)
       {
          if(args[i][0]=='>')
                {
                   fd[1]=open(args[i+1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
                   flag=1;
                }
            if(args[i]==">>" )
                {
                   fd[1]=open(args[i+1], O_APPEND|O_WRONLY, 0644);
                   flag=1;
                }
       }
       if (first == 1 && last == 0 && input == 0) {
           dup2( fd[1], 1 );
       } else if (first == 0 && last == 0 && input != 0) {
           dup2(input, 0);
           dup2(fd[1], 1);
       } else {
           if(flag==1)
            {
               dup2(fd[1],1);
            }
           dup2( input, 0 );
       }
         if(flag==1)
       {
                if(strcmp(args[1],">>")==0)
                   execlp(args[0], args[0], 0, (char *)0);
                else if(strcmp(args[1],">")==0)
                   execlp(args[0], args[0], 0, (char *)0);
                else
                   execlp(args[0], args[0], args[1], (char *)0);
       }
       else if (execvp( args[0], args) == -1)
           exit(1);
   }
  

   if (input != 0)
       close(input);
    close(fd[1]);
    if (last == 1)
       close(fd[0]);
   return fd[0];
}

static int run(char* cmd, int input, int first, int last);
static char line[1024];
static int n = 0;

int main()
{
   while (1) {
       printf("$$~> ");
       fflush(NULL);

       if (!fgets(line, 1024, stdin))
           return 0;

       int input = 0;
       int first = 1;

       char* cmd = line;
       char* next = strchr(cmd, '|');

       while (next != NULL) {
           *next = '\0';
           input = run(cmd, input, first, 0);

           cmd = next + 1;
           next = strchr(cmd, '|'); 
           first = 0;
       }
       input = run(cmd, input, first, 1);
       waiting(n);
       n = 0;
   }
   return 0;
}

static void tokenize(char* cmd);

static int run(char* cmd, int input, int first, int last)
{
   tokenize(cmd);
   if (args[0] != NULL) {
       if (strcmp(args[0], "exit") == 0)
           exit(0);
       n += 1;
       return command(input, first, last);
   }
   return 0;
}

static char* skipspace(char* s)
{
   while (isspace(*s)) ++s;
   return s;
}

static void tokenize(char* cmd)
{
   cmd = skipspace(cmd);
   char* next = strchr(cmd, ' ');
   int i = 0;

   while(next != NULL) {
       next[0] = '\0';
       args[i] = cmd;
       ++i;
       cmd = skipspace(next + 1);
       next = strchr(cmd, ' ');
   }

   if (cmd[0] != '\0') {
       args[i] = cmd;
       next = strchr(cmd, '\n');
       next[0] = '\0';
       ++i;
   }

   args[i] = NULL;
}

static void waiting(int n)
{
   int i;
   for (i = 0; i < n; ++i)
       wait(NULL);
}
