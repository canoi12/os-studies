#define _GNU_SOURCE
#include <sched.h>
//#include <utmpx.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <unistd.h>
#include <stdlib.h>
int * vec1;
int * vec2;

void* sum_vector(void* tid) {
	int x = (int)tid;
	int val = vec1[x] + vec2[x];
	printf("Sou a thread %d e o resultado da soma é %d\n", x, val);

}

int main(int argc, char ** argv) {
	int N = atoi(argv[1]);
	vec1 = (int *) malloc(sizeof(int) * N);
	vec2 = (int *) malloc(sizeof(int) * N);
	pthread_t threads[N];
	void * thread_return;

	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		vec1[i] = rand() % 100;
		vec2[i] = rand() % 100;
		printf("%d: %d %d\n", i, vec1[i], vec2[i]);
	}

	int i = 0;

	for (i = 0; i < N; i++) {
		pthread_create(&threads[i], NULL, sum_vector, (void*)i);
	}

	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], &thread_return);
	}

	return 0;
}