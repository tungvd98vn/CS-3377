#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	char line[256];
	char prompt[] = "SimpleShell: Enter command or exit % ";
	pid_t pid;
	while(1){
		printf("%s", prompt );
		/* Try getting input. If error or EOF, exit */
		while( fgets(line, sizeof line, stdin) != NULL ){	
			/* fgets leaves '\n' in input buffer. ditch it */
			line[strlen(line)-1] = '\0';
			if(strcmp(line,"exit") == 0){
			exit(0);
			}
			pid = fork();
			if(pid<0){
				fprintf(stderr, "fork failed");
				return 1; }
			else if(pid == 0){
				execlp(line,line, NULL);}
			else{
				wait(NULL);
				printf("child complete\n");
			}
}
return 0;
}
}

