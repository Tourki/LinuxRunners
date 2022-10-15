#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	while (1){
		char buf[100];
		fgets(buf,100,stdin);
		int ret_pid = fork();

		if (ret_pid < 0)
			printf("Fork failed\n");
		else if (ret_pid == 0){
			char *cmdargv[] = { NULL };
			char *cmdenvp[] = { NULL };
			buf[strlen(buf)-1]=0;
			execve(buf,cmdargv,cmdenvp);
		}
	}

	return 0;

}
