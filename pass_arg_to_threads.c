#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
// the argument of a routine function like void* arg if the 4th arg #include
// pthread_create function
void *routine(void *arg) {
	// int	index = *(int*)arg;
	// if you want that the number are printed ir order
	// just pass array in position casting it in create thread function (void*)(primes+i)
	printf("Primes numbers: %d\n", *(int*)arg);
	// in this case memory need to be freed here because 
	// if we free it in for loop, it can be freed before be used by routine function
	// free(arg);
}

int main(int ac, char **av)
{
	pthread_t th[10];
	for (int i = 0; i < 10; i++) {
		// int *idx = malloc(sizeof(int));
		// *idx = i;
		if (pthread_create(th + i, NULL, &routine, (void*)(primes + i)) != 0) {
			perror("Failed to create thread");
		}
	}
	for (int i = 0; i < 10; i++) {
		if (pthread_join(th[i], NULL) != 0) {
			perror("Failed to joinc thread");
		}
	}
	return (0);
}

// in this way it will go wrong, because because each thread don't start after for loop 
// calls thread create function.
// sometimes it will give the same number and or 0 because it will get a index
// that does not have a value.
// It need to be allocated like in function above! 
// -- -- - - -- - - - -- -- - - -- - --- - --- - -
// int main(int ac, char **av)
// {
// 	pthread_t th[10];
// 	for (int i = 0; i < 10; i++) {
// 		if (pthread_create(&th[i], NULL, &routine, &i) != 0) {
// 			perror("Failed to create thread");
// 		}
// 	}
// 	for (int i = 0; i < 10; i++) {
// 		if (pthread_join(th[i], NULL) != 0) {
// 			perror("Failed to joinc thread");
// 		}
// 	}
// 	return (0);
// }
