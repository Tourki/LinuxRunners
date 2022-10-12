#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int Dest, Source,bufSize;
	char buffer[255];
	struct stat statbuf;

	if (argc == 3)
	{
		//open the source file with read-only permissions
		Source = open(argv[1],O_RDONLY, S_IRUSR);
		//Fetch the source file access permissions
		stat(argv[1], &statbuf);
		Dest   = open(argv[2],O_WRONLY | O_CREAT, statbuf.st_mode);

		//check issues with opening the source file or creating the destination
		if (Source !=-1 && Dest != -1)
		{
			//Read buffer till read return 0 indicating end of file
			while(bufSize=read(Source,buffer,255))
				write(Dest,buffer,bufSize);
		}
		else
		{
			printf("Error: Source not found or couldn't create the destination file\n");
		}
		close(Source);
		close(Dest);
	}
	else
	{
		printf("Error: wrong number of arguments\n");
	}

	return 0;
}
