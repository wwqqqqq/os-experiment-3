#include <stdio.h>
#include <stdlib.h>
#include "msg_queue.c"

int main(int argc,char*argv[])
{
	mymsgbuf qbuf;
	int myqid;
	if(argc!=2){
		printf("USAGE: receiver <mtype>\n");
		exit(1);
	}
	if((myqid=open_queue())==-1){
		printf("open queue fail!\n");
		exit(1);
	}
	read_message(myqid,&qbuf,atoi(argv[1]));
	return 0;
}
