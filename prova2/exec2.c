#define _GNU_SOURCE
#include <sched.h>
//#include <utmpx.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int * vec;

void* multi_vector(void * tid) {
	int x = (int)tid;
	int x2 = x*2;
	int val = vec[x2] + vec[x2+1];
	printf("Sou a thread %d e o resultado da soma é %d\n", x, val);

}

int main(int argc, char ** argv) {
	int N = atoi(argv[1]);
	if (N%2 != 0) {
		printf("Numero deve ser par\n");
		exit(-1);
	}
	vec = malloc(sizeof(int) * N);
	pthread_t thread[N/2];
	void * thread_return;
	srand(time(NULL));

	int i;

	for (i = 0; i < N; i++) {
		vec[i] = rand() % 100;
		printf("%d: %d\n", i, vec[i]);
	}

	for (i = 0; i < (N/2); i++) {
		pthread_create(&thread[i], NULL, multi_vector, (void*)i);
	}

	for (i = 0; i < (N/2); i++) {
		pthread_join(thread[i], &thread_return);
	}
	return 0;
}