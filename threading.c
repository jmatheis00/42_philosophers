#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * routine(void *tid)
{
	// cast thread ID
	long *myID = (long *) tid;
	printf("This is thread %ld\n", *myID);
	return (NULL);
}

int main()
{
	pthread_t tid0; //to identify the thread we are creating
	pthread_t tid1;
	pthread_t tid2;

	pthread_t *pthreads[] = {&tid0,&tid1,&tid2};

	int i = 0;
	while(i < 3)
	{
		pthread_create(pthreads[i], NULL, routine, (void *)pthreads[i]);
		i++;
	}
	// 2. arg: if NULL-> default behavior
	// pthread_exit (NULL); // forces the thread to finish
	return (0);
}