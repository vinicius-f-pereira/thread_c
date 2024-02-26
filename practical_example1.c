#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void *routine(void *arg) {
	int	idx = *(int*)arg;
	int	sum = 0;
	for (int i = 0; i < 5; i++) {
		sum += primes[idx + i];
	}
	printf("Local Sum: %d\n", sum);
	// free(arg);
	*(int*)arg = sum;
	return arg;
}

int main(int ac, char **av)
{
	pthread_t th[2];
	for (int i = 0; i < 2; i++) {
		int *idx = malloc(sizeof(int));
		*idx = i * 5;
		if (pthread_create(th + i, NULL, &routine, idx) != 0) {
			perror("Failed to create thread");
		}
	}
	int globalSum = 0;
	for (int i = 0; i < 2; i++) {
		int	*result;
		if (pthread_join(th[i], (void**)&result) != 0) {
			perror("Failed to joinc thread");
		}
		globalSum += *result;
		free(result);
	}
	printf("Sum numbers: %d\n", globalSum);
	return (0);
}
