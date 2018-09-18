
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
int   p[2];
int   r;
pid_t pid;

pipe(p);
if ((pid = fork()) == 0)
{
  dup2(p[1], 1);
  close(p[0]);
  close(p[1]);
  execvp(command[0], command);
}

if ((pid = fork()) == 0)
{
  dup2(p[0], 0);
  close(p[1]);
  close(p[1]);
  r = execvp(comand_next[0], command_next);
}

close(p[0]);
close(p[1]);
wait(NULL);
wait(NULL);
return r;
And this is a second version:

 int i = 0;
int t[3] = {0, 0, 0};;

while (i < 3)

{
 pipe(p);
 if ((pid = fork()) == 0)
 {
   dup2(t[i], 0);
   if (i < 2)
       dup2(p[1], 1);
   close(p[0]);
 r=  execvp(cmd[i][0], cmd[i]);
 }
 else
 {
     wait(NULL);
     close(p[1]);
     i += 1;
     t[i] = p[0];
 }
}
