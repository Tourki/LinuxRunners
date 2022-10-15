#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


bool AllIsWhiteSpaces(char *s){
	int  i=0;
	for(i=0;s[i]!='\0';i++){
		if(s[i]!=' ' && s[i]!='\t')
			return false;
    }
	return true;
}

void ReplaceTabsWithSpaces(char *s){
	int  i=0;
	for(i=0;s[i]!='\0';i++)
		s[i]=(s[i]=='\t')?' ':s[i];
}

void Parser(char *buf,char *cmd, char **cmdargv)
{
   char * token;
   int argCount;
   //replace tabs with spaces to unify the delimiter
   ReplaceTabsWithSpaces(buf);
   //use string token to separate the args
   token = strtok(buf, " ");
   //set the command string
   strcpy(cmd,token);
   //set the first cmdargv
   cmdargv[0]=cmd;
   //set the first the remaining args and end with NULL
   for(argCount=1; token != NULL; argCount++) {
	  token = strtok(NULL, " ");
	  cmdargv[argCount]=token;
   }
}

int main(int argc, char *argv[])
{
	char buf[100]="";
	char cmd[100]="";
	char *cmdargv[100] = { NULL };
	int status;

	while (1){
		//print the shell header and get the input
		printf("tourki@localshell$ ");
		gets(buf);

		//if the input all white spaces then skip this iteration
		if (AllIsWhiteSpaces(buf) == false){
			//Parse the command arguments
			Parser(buf,cmd,cmdargv);
			//if the command is exit then exit the shell program
			if (strcmp(buf,"exit")==0){
				break;
			}
			//else if(){}
			//if it is not a build in command then fork
			else{
				int ret_pid = fork();

				if (ret_pid < 0)
					printf("Fork failed\n");
				else if (ret_pid > 0){
					//the parent process wait for the child to change its status
					wait(&status);
				}
				else if (ret_pid == 0){
					//the child process calls the command and exit upon failure
					execvp(cmd,cmdargv);
					printf("%s: command not found\n",buf);
					break;
				}
			}
		}
	}

	return 0;

}
