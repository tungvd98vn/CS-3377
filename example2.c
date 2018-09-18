// minishell part 1 - Shell sample code with execvp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG 10

int pid_child;

/*** Main ***/

void sighand(int signum);


int main(){
    // declare variables
    char *prompt = "sh1$ ";
    char line[256];
    char line1[256];

    char program[32], command[32], *args[MAX_ARG];
    int pid, status, i;

    // print the prompt
    printf("%s", prompt);
    // Try getting input. If error or EOF, exit

    while(fgets(line, sizeof line, stdin) != NULL)
    {
        // fgets leaves '\n' in input buffer. ditch it
        line[strlen(line)-1] = '\0';
        strcpy(line1,line);
        // If the input is not null, get in
        if (line != NULL) {
		 
            // parse command and arg
            args[0] = strtok(line, " "); 	// grab command

            for(i=1; i<10; i++) 			// grab arguments
                args[i] = strtok(NULL, " ");

            strcpy(command, args[0]);	// store command variable

            // check to see if the command is 'exit'
            if(!strcmp("exit", args[0])) {
                exit(0);
            }
            // check to see if the command is 'cd'
            else if(!strcmp("cd", args[0])) {
                chdir(args[1]);
            }
            // handles all other commands
            else {
		   pid = fork(); // fork to create new child    

		   if(pid == 0) { // code to be run by the child	
 		  signal(SIGTSTP, SIG_IGN);
                    status = execvp(command, args); // execute
                    exit(0); 			     // exit child
                }
                else { 	      // code to be run by the parent
                    pid_child = pid;
			  signal(SIGTSTP, sighand);
                    waitpid(-1); // wait for children to finish
			  signal(SIGTSTP, SIG_DFL);
                }
            }
        }

	// print the prompt
    	printf("%s", prompt );
    }
    return 0;
}

void sighand(int signum)
{
/* supposedly need to reset this here (per "man signal" and
   it's discussion of signals under linux), but doesn't actually
   seem to matter. Documentation != observed program behavior. */

  //signal(signum, nyahnyah);
  kill(pid_child,SIGKILL);
  fprintf(stderr, "nyah, nyah Mr. #%d.\n", signum);
}
