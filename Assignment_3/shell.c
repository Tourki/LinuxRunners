#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
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

typedef struct{
	char * varName;
	char * varValue;
}localVar;

bool findAndAddLocalVariable(char* buf,localVar ** localVariables, int *localVarNum){
   char * varName;
   char * varValue;
   int startlocalVarNum = *localVarNum;
   int i;
   bool newVariable=true;
   //store the first variable
   varName = strtok(buf, "=");
   varValue = strtok(NULL, "=");
   if((varName != NULL) && (varValue != NULL)){
	   //search the existing variable list
	   for (i=0;i<startlocalVarNum;i++){
		   //if the variable name already exists then update its value
		   if(strcmp((*localVariables)[i].varName,varName)==0){
			   free((*localVariables)[i].varValue);
			   (*localVariables)[i].varValue=malloc(strlen(varValue));
			   strcpy((*localVariables)[i].varValue,varValue);
			   newVariable=false;
		   }
	   }
	   //add a new variable
	   if(newVariable){
		   (*localVariables) = (localVar *) realloc((*localVariables),(sizeof(localVar)*(++(*localVarNum))));
		   (*localVariables)[(*localVarNum)-1].varName=malloc(strlen(varName));
		   strcpy((*localVariables)[(*localVarNum)-1].varName,varName);
		   (*localVariables)[(*localVarNum)-1].varValue=malloc(strlen(varValue));
		   strcpy((*localVariables)[(*localVarNum)-1].varValue,varValue);
	   }
   }
   return ((varName != NULL) && (varValue != NULL));
}

void listLocalVariables(localVar * localVariables, int localVarNum){
	int i;
	//list all the local variables
   for (i=0;i<localVarNum;i++)
	   printf("localVariable[%d]: %s = %s\n",i,localVariables[i].varName,localVariables[i].varValue);
}

void exportLocalVariables(char **cmdargv,localVar * localVariables, int localVarNum){
   int i,j;
   bool varFound=false;
   for (j=1;cmdargv[j]!=NULL;j++){
	   //search for the exported variable
	   for (i=0;i<localVarNum;i++){
		   if(strcmp(localVariables[i].varName,cmdargv[j])==0){
			  varFound=true;
			  break;
		   }
	   }
	   //export the variable if found or print an error
	  if(varFound==true){
		  setenv(localVariables[i].varName,localVariables[i].varValue,1);
	   	  varFound=false;
	  }
	  else
		  printf("undefined variable %s\n",cmdargv[j]);
   }
}

int main(int argc, char *argv[])
{
	char buf[100]="";
	char cmd[100]="";
	char *cmdargv[100] = { NULL };
	localVar * localVariables = NULL;
	int localVarNum=0;
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
			else if(findAndAddLocalVariable(buf,&localVariables,&localVarNum)){
				//do nothing the variable has been stored
				continue;
			}
			else if(strcmp(buf,"set")==0){
				listLocalVariables(localVariables,localVarNum);
			}
			else if(strcmp(cmd,"export")==0){
				exportLocalVariables(cmdargv,localVariables,localVarNum);
			}
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
