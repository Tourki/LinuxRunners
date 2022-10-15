#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


bool AllIsWhiteSpaces(char *s)
{
	int  i=0;
	for(i=0;s[i]!='\0';i++)
    {
		if(s[i]!=' ' && s[i]!='\t')
			return false;
    }
	return true;
}

int main(int argc, char *argv[])
{
	char buf[100]="";
	char *cmdargv[] = { NULL };
	int status;

	while (1){
		printf("tourki@localshell$ ");
		gets(buf);
		if (AllIsWhiteSpaces(buf) == false){

			int ret_pid = fork();

			if (ret_pid < 0)
				printf("Fork failed\n");
			else if (ret_pid > 0){
				wait(&status);
			}
			else if (ret_pid == 0){
				execvp(buf,cmdargv);
				printf("%s: command not found\n",buf);
				break;
			}
		}
	}

	return 0;

}
