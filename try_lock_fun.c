#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

pthread_mutex_t	mutex;

void *routine() {
	if (pthread_mutex_trylock(&mutex) == 0) {
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	} else {
		printf("Didn't Get lock\n");
	}

}

int main(int ac, char **av)
{
	pthread_t	th[4];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++) {
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Error creating thread");
		}
	}
	for (int i = 0; i < 4; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Error joining thread");
		}
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
