

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include <dirent.h>
#include<signal.h> // for exit
#define MAXLINE 1024
#define COPYMORE 0644
char *
getinput(char *buffer, size_t buflen, char *prt) {

	printf("\n%s", prt);
	return fgets(buffer, buflen, stdin);

}
void copy(char *line, char **buff)
{
while (*line != '\0') { 
while (*line == ' ' || *line == '\t' || *line == '\n')
*line++ = '\0';   
*buff++ = line; 
while (*line != '\0' && *line != ' ' &&
*line != '\n' && *line != '\t')
line++;
}
*buff = '\0'; 
}
int main(int argc, char **argv) {
	char buf[1024];
	pid_t pid;
	int status;
	char cmd[22];
	char red[22];
	char argu[22];
	char option[22];
	char file[22];
	int n = 0;
	int pid2;
	int pc[2]; 
	int cp[2]; 
	char ch;
 char *rcmd[1024];
	char promt[3] = { '$', '$', '\0' };
	while (1) {

getinput(buf, sizeof(buf), promt);
		//buf[strlen(buf) - 1] = '\0';
		if (buf[0] == '#' && buf[1] == '#')
		{
			promt[0] = '#'; promt[1] = '#';
		}
		if (buf[0] == '%' && buf[1] == '%')
		{
			promt[0] = '%'; promt[1] = '%';
		}

		



		int o = 0;
		//////////////parse //////////////
		printf("buf: %s\n", buf);

		//printf("0 element : %c\n", buf[2]);
		while (buf[n] != '\0'){

			if (n == 0){
memset(cmd, 0, 22);

				while (buf[n] != ' ' && buf[n] != '\0'&& buf[n] != ';'&&buf[n] != '<' && buf[n] != '>' && buf[n] != '.'&& buf[n] !='|'){
					cmd[n] = buf[n];
					n++;
				}
				cmd[n] = '\0';
				n--;
				printf("Command :%s\n", cmd);

			}


			if (buf[n] == '|')
			{
				printf("\nPipe\n");
				n++;
				
				while (buf[n] != ' ' && buf[n] != '\0'&& buf[n] != ';'){
					cmd[o] = buf[n];
					n++;
					o++;
				}
				cmd[o] = '\0';
				n--;
				printf("Command :%s", cmd);

			}



			if (buf[n] == ';'){
				memset(cmd, 0, 22);
				n++;
				
				while (buf[n] != '\0'&& buf[n] != ' '&& buf[n] != ';'&& buf[n] != '<'&& buf[n] != '>'){
					cmd[o] = buf[n];
					n++;
					o++;
					//printf("ENDD");
				}
				o++;
				cmd[o] = '\0';
				o = 0;

				printf("Command :%s", cmd);
				n--;
			}
			////parse option///////

			if (buf[n] == '-'){
				o = 0;
				while (buf[n] != ' '&& buf[n] != '\0' && buf[n] != ';'&&buf[n] != '|'){
					option[o] = buf[n];
					n++;
					o++;
				}

				option[o] = '\0';
				o = 0;

n--;
				printf("\nOption :%s", option, "\n");

			}

			if (buf[n] == '<' || buf[n] == '>' || buf[n] == '*' || buf[n] == '&')
			{
				memset(file, 0, 22);
memset(red, 0, 22);
				while ( buf[n] == '<' || buf[n] == '>' ){
					red[o] = buf[n];
					n++;
					o++;
				}

				red[o] = '\0';
				printf("\nFile Redirection: %s\n", red);

				o = 0;
				


				while (buf[n] != ' '&& buf[n] != '\0'&& buf[n] != ';'&& buf[n] != '|'){
					file[o] = buf[n];
					n++;
					o++;
				}
				printf("\nFile: %s\n", file);



					n--;
				

				file[o] = '\0';
				o = 0;
			}



			if (buf[n] == '/'){
				while (buf[n] != ' '&& buf[n] != '\0'){
					argu[o] = buf[n];
					n++;
					o++;
				}
				
				argu[o] = '\0';
				o = 0;
				printf("\narguuments :");
				while (o < strlen(argu)){
					printf("%c", argu[o]);
					o++;
				}
				printf("\n");

				n--;
			}
		
			n++;
		}
		//////////////file output/////////////////////
		char line;
		//


		if (red[0] == '>'){
		FILE *ifp, *ofp;
char *mode = "r";
char outputFilename[] = "out.list";

ifp = fopen(file, mode);


ofp = fopen(outputFilename, "w");


  fprintf(ofp, "%s %d\n",system("ls"));


		}
		

		



		printf("\nEnd of command.");
		n = 0;
		////////////////////// End of parse

 copy(buf,rcmd);
 if(rcmd[1]!=NULL && strcmp(rcmd[1],"|")==0)   
       {

       int pipe_fds[2];
       pid_t p,p1,p2,p3,p4;

       int stdin_save, stdout_save;
       char str[80];
       int fp;
       if (pipe(pipe_fds) < 0)
           return -1;
       stdin_save = dup(STDIN_FILENO);
       stdout_save = dup(STDOUT_FILENO);

       p=fork();

       if(p==0)
       {
       close(pipe_fds[0]);
       strcpy(str,"./");
     
      
   
       dup2(pipe_fds[1],STDOUT_FILENO);

     
       strcat(str,rcmd[0]);

       if(execvp(str,&rcmd[0])==-1)
           {
           perror("invalid");
           exit(1);
           }

       //exit(1);
      
       }
       else
       {
       wait(NULL);
       p1=fork();
       if(p1==0)
       {
              
       close(pipe_fds[1]);
       dup2(pipe_fds[0],STDIN_FILENO);
       strcpy(str,"./");
       strcat(str,rcmd[2]);
       if( execvp(str,&rcmd[2])==-1)
           {
           perror("invalid");
           exit(1);
           }

    
       exit(1);
       }
           else if(rcmd[4]!=NULL)
           {
       wait(NULL);
       p2=fork();
               if(p2==0 )
               {
       close(pipe_fds[1]);
     

    
       dup2(pipe_fds[0],STDIN_FILENO);
       dup2(pipe_fds[1],STDOUT_FILENO);
     
	 
       strcpy(str,"./");
       strcat(str,rcmd[4]);
       if(execvp(str,&rcmd[4])==-1)
           {
       perror("invalid");
       exit(1);
       }
               }
           }



       exit(1);

       }
      
       }
      
if(strstr(buf,"list"))system("ls");       

       else system(buf);       


      
		
		
		
		//if(buf[n] == '\0'){exit(0);}

		if (strcmp(buf, "exit") == 0 || strcmp(buf, "quit") == 0){
			exit(1);
		}



			}

}





