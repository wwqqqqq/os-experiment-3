#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(void)
{
	int segment_id;
	char * shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;

	//allocate a shared memory segment
	segment_id=shmget(IPC_PRIVATE,shared_segment_size,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	//attach the shared memory segment
	shared_memory=(char*)shmat(segment_id,0,0);
	printf("shared memory attached at address %p\n",shared_memory);
	//determine the segment's size
	shmctl(segment_id,IPC_STAT,&shmbuffer);
	segment_size=shmbuffer.shm_segsz;
	printf("segment size: %d\n",segment_size);
	//write a string to the shared memroy segment
	strcpy(shared_memory,"hello world");
	shmdt(shared_memory);

	//reattach the shared memory segment, at a different address
	shared_memory=(char*)shmat(segment_id,(void*)0x5000000,0);
	printf("shared memory reattached at address %p\n",shared_memory);
	//printf out the string from shared memory
	printf("%s\n",shared_memory);
	//detach the shared memory segment
	shmdt(shared_memory);

	//deallocate the shared memory segment
	shmctl(segment_id,IPC_RMID,0);

	return 0;
}
