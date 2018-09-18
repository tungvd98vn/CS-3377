#include <stdio.h>
#include<stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h> 
#include <string.h>
#include <sys/types.h>
#include<dirent.h> 
#include <unistd.h>
#include<signal.h>  
#define MAXLINE 1024
#define COPYMORE 0644

void copy(char *line, char **argv)
{
while (*line != '\0') {
while (*line == ' ' || *line == '\t' || *line == '\n')
*line++ = '\0';  
*argv++ = line; 
while (*line != '\0' && *line != ' ' &&
*line != '\t' && *line != '\n')
line++;
}
*argv = '\0';  
}

int main()
{
   char par[100];
   char *arg[100];
  
   while (1)
   {
       printf("custom-shell:");
       gets(par);
       copy(par,arg);    
      
       if(arg[1]!=NULL && strcmp(arg[1],"|")==0)  
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
       signal(SIGCHLD,SIG_IGN);

       if(p==0)
       {
       close(pipe_fds[0]);
       strcpy(str,"./");
      
       dup2(pipe_fds[1],STDOUT_FILENO);

       strcat(str,arg[0]);

       if(execvp(str,&arg[0])==-1)
           {
           perror("invalid");
           exit(1);
           }

       exit(1);
      
        close(pipe_fds[1]);
        dup2(stdout_save, STDOUT_FILENO);
      
       }
       else
       {
       wait(NULL);
       p1=fork();
       if(p1==0)
       {
              
       close(pipe_fds[1]);
     
        dup2(stdout_save,STDOUT_FILENO);

      
       dup2(pipe_fds[0],STDIN_FILENO);


       strcpy(str,"./");
       strcat(str,arg[2]);
       if( execvp(str,&arg[2])==-1)
           {
           perror("invalid");
           exit(1);
           }

     
        close(pipe_fds[0]);


        dup2(stdin_save, STDIN_FILENO);
       exit(1);
       }
           else if(arg[4]!=NULL)
           {
       wait(NULL);
       p2=fork();
               if(p2==0 )
               {
       close(pipe_fds[1]);

       dup2(stdout_save,STDOUT_FILENO);

  
       dup2(pipe_fds[0],STDIN_FILENO);
       dup2(pipe_fds[1],STDOUT_FILENO);
       strcpy(str,"./");
       strcat(str,arg[4]);
       if(execvp(str,&arg[4])==-1)
           {
       perror("invalid");
       exit(1);
       }
               }
           }


       exit(1);

       }
      
       }
      
       if(strstr(par,"list"))system("ls");  
       else if(strstr(par,"exit"))break;       
       else system(par);      
   }
   return 0;
}
