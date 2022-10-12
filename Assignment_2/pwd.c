#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		//get the current working directory
		char *cwd = get_current_dir_name();

		//make sure we can get the current path with no errors
		if ( cwd != NULL)
			printf("%s\n",get_current_dir_name());
		else
			printf("Error in obtaining the pathname of the current working directory\n");
	}
	else
	{
		printf("Error: too many arguments\n");
	}
	return 0;
}
