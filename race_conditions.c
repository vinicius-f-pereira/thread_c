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
	pthread_t	t1;
	pthread_t	t2;
	pthread_t	t3;
	pthread_t	t4;

	pthread_mutex_init(&mutex, NULL);
	// function to create a thread
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_create(&t3, NULL, &routine, NULL) != 0)
		return (5);
	if (pthread_create(&t4, NULL, &routine, NULL) != 0)
		return (6);

	// function to wait for threads
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	if (pthread_join(t3, NULL) != 0)
		return (7);
	if (pthread_join(t4, NULL) != 0)
		return (8);
	pthread_mutex_destroy(&mutex);
	//print number of  mails
	printf("Number of mails %d\n", mails);
	return (0);
}
