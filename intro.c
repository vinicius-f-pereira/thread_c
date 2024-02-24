#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *routine() {
	printf("test for threads\n");
	sleep(3);
	printf("End of threads\n");
}

int main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;
	// function to create a thread
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	// function to wait for threads
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
}
