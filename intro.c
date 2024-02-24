#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *routine() {
	printf("test for threads");
}
int main(int ac, char **av)
{
	pthread_t	t1;
	pthread_create(&t1, NULL, &routine, NULL);
	return (0);
}
