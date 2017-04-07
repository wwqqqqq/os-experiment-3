#include <stdio.h>
#include "msg_queue.c"

int main(void)
{
	int myqid;
	if((myqid=open_queue())==-1){
		printf("open queue fail!\n");
		exit(1);
	}
	remove_queue(myqid);
	printf("Remove queue %d\n",myqid);
	return 0;
}
