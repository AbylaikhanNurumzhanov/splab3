#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 
#include <stdarg.h>   
#include <stdio.h>
int main() 
{
	pid_t process = fork();
	if(process<0){
		abort();
	}
	else if(process==0){
 		char string[100];
		strcpy(string, "/bin/bash AbaV1.sh ");
 		
		char *name[] = { "/bin/bash","-c",string,NULL};
		execvp(name[0], name);
	}

	else{ 
		waitpid(process,0,0);
	}
}
