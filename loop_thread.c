#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int	mails = 0;
pthread_mutex_t mutex;

void *routine() {
	// in this case race condition will happen (have others too)
	// for (int i = 0; i < (INT_MAX/2); i++)
	// 	mails++;

	// to avoid it, we need to do it in this way	
	for (int i = 0; i < 1150; i++){
		//lock the variable so only one process can use it at once.
		pthread_mutex_lock(&mutex);
		mails++;
		//so.. this to unlock after use...
		pthread_mutex_unlock(&mutex);
	}
}

int main(int ac, char **av)
{
	// we dont need to create threads one by one, we can use array too.
	pthread_t	threads[4];
	size_t i;

	pthread_mutex_init(&mutex, NULL);
	// loop to create threads (this way to do this loop is not good, things I'll not work \
	// like threads are used to work)
	for (i = 0; i < 4; i++)
	{
		// function to create a thread
		if (pthread_create(threads + i, NULL, &routine, NULL) != 0) {
			perror ("Failed to create thread");
			return (1);
		}
		printf("Thread %d started\n", i);
		// function to wait for threads
		if (pthread_join(threads[i], NULL) != 0)
			return (2);
		printf("Thread %d finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	//print number of  mails
	printf("Number of mails %d\n", mails);
	return (0);
}
