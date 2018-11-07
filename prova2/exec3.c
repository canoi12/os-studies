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
	printf("Sou a thread %d na cpu %d e o resultado da soma é %d\n", x, sched_getcpu(), val);

}

int create_thread_on_cpu(pthread_t* thread, pthread_attr_t* attr, cpu_set_t* cpu_set, int cpu_number) {

}

int main(int argc, char ** argv) {
	int i, NPROC, N;
	N = atoi(argv[1]);
	if (N%2 != 0) {
		printf("Numero deve ser par\n");
		exit(-1);
	}
	vec = malloc(sizeof(int) * N);

	pthread_t thread[N/2];
	void * thread_return;
	pthread_attr_t attr;
	cpu_set_t cpu_set;

	NPROC = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Número de processadores: %d\n", NPROC);

	pthread_attr_init(&attr);

	srand(time(NULL));

	for (i = 0; i < N; i++) {
		vec[i] = rand() % 100;
		printf("%d: %d\n", i, vec[i]);
	}

	for (i = 0; i < (N/2); i++) {
		int cpu = i%NPROC;
		CPU_ZERO(&cpu_set);
		CPU_SET(cpu, &cpu_set);
		pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpu_set);
		pthread_create(&thread[i], &attr, multi_vector, (void*)i);
	}

	for (i = 0; i < (N/2); i++) {
		pthread_join(thread[i], &thread_return);
	}
	return 0;
}