#include <stdio.h>
#include <string.h>

int main()
{
	//Create a buffer for the input
	char Input[100]="";
	//Keep printing the input unless it's "exit"
	while(strcmp(Input,"exit")!=0)
	{
		printf("Ana Gahez ya Basha > ");
	    gets(Input);
	    printf("Yout said: %s\n",Input);
	}
	printf("Good Bye :)\n");
	return 0;
}
