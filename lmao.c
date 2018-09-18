#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h> //for file status description
#include <string.h>
#include <sys/types.h>
#include<dirent.h> //for readdir--ls command
#include <unistd.h>
#include<signal.h> // for exit
#define MAXLINE 1024
#define COPYMORE 0644

void copy(char *line, char **argv)
{
while (*line != '\0') { //if not the end of line
while (*line == ' ' || *line == '\t' || *line == '\n')
*line++ = '\0'; //replace white space with null   
*argv++ = line; //save argument position
while (*line != '\0' && *line != ' ' &&
*line != '\t' && *line != '\n')
line++;//skip character until blank space
}
*argv = '\0';//mark the end of argument   
}

int main()
{
   char par[100];
   char *arg[100];
  
   while (1)
   {
       printf("custom-shell:");
       gets(par);
       copy(par,arg);       //copying par into arg
      
       if(arg[1]!=NULL && strcmp(arg[1],"|")==0)   //using pipe
       {

       int pipe_fds[2];
       pid_t p,p1,p2,p3,p4;

       int stdin_save, stdout_save;
       char str[100];
       int fp;
       if (pipe(pipe_fds) < 0)
           return -1;
       stdin_save = dup(STDIN_FILENO);
       stdout_save = dup(STDOUT_FILENO);

       p=fork();
       //signal(SIGCHLD,SIG_IGN);

       if(p==0)
       {
       close(pipe_fds[0]);
       strcpy(str,"./");
       //Duplicate stdin and stdout so we can restore them later.
      
       // Make the write end of the pipe stdout.
       dup2(pipe_fds[1],STDOUT_FILENO);

       /* Run the program. Its output will be written to the pipe. */
       strcat(str,arg[0]);

       if(execvp(str,&arg[0])==-1)
           {
           perror("invalid");
           //exit(1);
           }

       exit(1);
       /* Close the write end of the pipe. */
           //close(pipes_fd[1]);
           //dup2(stdout_save, STDOUT_FILENO);
      
       }
       else
       {
       wait(NULL);
       p1=fork();
       if(p1==0)
       {
              
       close(pipe_fds[1]);
       /* Restore stdout. */
       // dup2(stdout_save,STDOUT_FILENO);

       /* Make the read end of the pipe stdin. */
       dup2(pipe_fds[0],STDIN_FILENO);


       /* Run another program. Its input will come from the output of the
           first program. */
       strcpy(str,"./");
       strcat(str,arg[2]);
       if( execvp(str,&arg[2])==-1)
           {
           perror("invalid");
           exit(1);
           }

       /* Close the read end of the pipe. */
       // close(pipe_fds[0]);

       /* Restore stdin. */
       // dup2(stdin_save, STDIN_FILENO);
       exit(1);
       }
           else if(arg[4]!=NULL)
           {
       wait(NULL);
       p2=fork();
               if(p2==0 )
               {
       close(pipe_fds[1]);
       /* Restore stdout. */
       //dup2(stdout_save,STDOUT_FILENO);

       /* Make the read end of the pipe stdin. */
       dup2(pipe_fds[0],STDIN_FILENO);
       dup2(pipe_fds[1],STDOUT_FILENO);
       /* Run another program. Its input will come from the output of the
           first program */
       strcpy(str,"./");
       strcat(str,arg[4]);
       if(execvp(str,&arg[4])==-1)
           {
       perror("invalid");
       //exit(1);
       }
               }
           }


       /* Close the read end of the pipe. */

       exit(1);

       }
      
       }
      
       if(strstr(par,"list"))system("ls");       //if list command system executes ls
       else if(strstr(par,"exit"))break;       //if exit command then it terminates
       else if(strstr(par,"quit"))break;       //if quit command then also it terminates.
       else system(par);       //command parsing using system
   }
   return 0;
}