#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 100
int main(int argc,char *argv[])
{
	int fd[2],nbytes;
	pid_t childpid;
	//char string[]="Hello world!";
    char buffer[BUFFER_SIZE];
    
	if(argc!=2){
		printf("USAGE: pipe <string>\n");
		exit(1);
	}
	
	/* fd[0] is set up for reading, fd[1] is set up for writing*/
	pipe(fd);
	if((childpid=fork())==-1)//fork fail
	{
		printf("fork fail!\n");
		exit(1);
	}
    
	//An example in which the parent wants to receive data from the child

	if(childpid==0)//child process
	{
		//closes up input side of pipe
		close(fd[0]);
		write(fd[1],argv[1],(strlen(argv[1])+1));//send the string through the output side of the pipe
		exit(0);
	}
	else//parent process
	{
		//closes up output side of pipe
		close(fd[1]);
		nbytes=read(fd[0],buffer,sizeof(buffer));//receive the string through the input side of the pipe
		printf("Received string: %s\nsize = %d bytes\n\n",buffer,nbytes);
	}

	return 0;
}
