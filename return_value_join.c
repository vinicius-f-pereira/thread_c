#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void *roll_dice() {
	int	value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	// printf("%d\n", value);
	return ((void*)result);
}

int main(int ac, char **av)
{
	int	*res;
	int	i;
	srand(time(NULL));
	pthread_t	th[8];
	for (i = 0; i < 8; i++) {
		// function to create a thread
		if (pthread_create(th + i, NULL, &roll_dice, NULL) != 0)
			return (1);
	}
	for (i = 0; i < 8; i++) {
		// function to wait for threads
		if (pthread_join(th[i], (void**) &res) != 0)
			return (3);
		printf("Result: %d\n", *res);
		free(res);
	}
	return (0);
}
