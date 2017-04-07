#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define SHARED_SEGMENT_SIZE 0x6400

void generate_segment(void);
void delete_segment(int segment_id);
void write(int segment_id,char *string);
void read(int segment_id);

int main(int argc,char *argv[])
{
	/*
	   shared_mem (g)en : generate shared memory segment, print the segment_id
	   shared_mem (d)el <segment_id> : delete the shared memory segment
	   shared_mem (w)rite <segment_id> <string> : write the string in the shared memory segment
	   shared_mem (r)ead <segment_id> : read the string in the shared memory segment
       shared_mem (s)tate : check the shared memory segment state
    */
	if(argc==1)
	{
		printf("USAGE: shared_mem g\n");
		printf("                  d <segment_id>\n");
		printf("                  w <segment_id> <string>\n");
		printf("                  r <segment_id>\n");
		printf("                  s\n");
		exit(1);
	}
	switch(tolower(argv[1][0]))
	{
		case 'g': generate_segment();break;
		case 'd': delete_segment(atoi(argv[2]));break;
	    case 'w': write(atoi(argv[2]),argv[3]);break;
	    case 'r': read(atoi(argv[2]));break;
		case 's': system("ipcs -m");break;
		default : 
		{
			   printf("USAGE: shared_mem g\n");
			   printf("                  d <segment_id\n");
			   printf("                  w <segment_id> <string>\n");
			   printf("                  r <segment_id>\n");
			   printf("                  s\n");
			   exit(1);
		}
	}
	return 0;
}

void generate_segment(void)
{
   int segment_id;
   segment_id=shmget(IPC_PRIVATE,SHARED_SEGMENT_SIZE,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
   printf("Generating segment...\nsegment id = %d\n",segment_id);
}
void delete_segment(int segment_id)
{
	shmctl(segment_id,IPC_RMID,0);
	printf("Deleting segment %d ...\n",segment_id);
}
void write(int segment_id,char *string)
{
	char *shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	shared_memory=(char*)shmat(segment_id,0,0);
	printf("shared_memory attached at address %p\n",shared_memory);
	shmctl(segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("segment size = %d\n",segment_size);
	strcpy(shared_memory,string);
	printf("Writing string to the segment...\n");
	shmdt(shared_memory);
}
void read(int segment_id)
{
	char * shared_memory;
	shared_memory=(char*)shmat(segment_id,0,0);
	printf("Shared_memory attached at address %p\n",shared_memory);
	printf("Reading the message...\nText: %s\n",shared_memory);
	shmdt(shared_memory);
}
