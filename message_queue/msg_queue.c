#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SEND_SIZE 80

typedef struct{
	long mtype; //message type
	char mtext[MAX_SEND_SIZE];
}mymsgbuf;
extern int open_queue(void);
extern void send_message(int qid,mymsgbuf * qbuf, long type, char *text);
extern void read_message(int qid,mymsgbuf * qbuf, long type);
extern void remove_queue(int qid);
extern void change_queue_mode(int qid, char * mode);


int open_queue(void)
{
	key_t key;
	int msgqueue_id;

	//create unique key via call to ftok()
	key=ftok(".",'m');

	//open the queue (create if necessary)
	if((msgqueue_id=msgget(key,IPC_CREAT|0660))==-1){
		perror("msgget");
		return -1;
	}
	return msgqueue_id;
}

void send_message(int qid,mymsgbuf *qbuf,long type,char *text)
{
	//send a message to the queue
	printf("Sending a message...(qid:%d)\n",qid);
	qbuf->mtype=type;
	strcpy(qbuf->mtext,text);
	if((msgsnd(qid,(struct msgbuf*)qbuf,strlen(qbuf->mtext)+1,0))==-1){
		perror("msgsnd");
		exit(1);
	}
}

void read_message(int qid,mymsgbuf *qbuf,long type)
{
	//read a message from the queue
	printf("Reading a message...(qid:%d)\n",qid);
	qbuf->mtype=type;
	msgrcv(qid,(struct msgbuf *)qbuf, MAX_SEND_SIZE,type,0);
	printf("Type: %ld Text: %s\n",qbuf->mtype,qbuf->mtext);
}

void remove_queue(int qid)
{
	//remove the queue
	msgctl(qid,IPC_RMID,0);
}

void change_queue_mode(int qid,char * mode)
{
	struct msqid_ds myqueue_ds;
    //get current info
	msgctl(qid,IPC_STAT,&myqueue_ds);
	//convert and load the mode
	sscanf(mode,"%ho",&myqueue_ds.msg_perm.mode);
	//update the mode
	msgctl(qid,IPC_SET,&myqueue_ds);
}
