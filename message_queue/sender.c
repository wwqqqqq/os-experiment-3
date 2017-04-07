#include <stdio.h>
#include <stdlib.h>
#include "msg_queue.c"
#include <string.h>

int main(int argc,char *argv[])
{
	int myqid;
	mymsgbuf qbuf;
    if(argc!=3){
		printf("USAGE: sender <mtype> <mtext>\n");
		exit(1);
	}
    if((myqid=open_queue())==-1){
		printf("open queue fail!\n");
		exit(1);
	}
	send_message(myqid,&qbuf,atoi(argv[1]),argv[2]);
	return 0;
}


