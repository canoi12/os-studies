#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 1000000
int * buffer;
int N;
int pos = 0;
pthread_mutex_t mutex;
pthread_cond_t condcons, condprod;

/*int buffer_cheio() {
	int i;
	for ( i = 0; i < N; i++ ) {
		if (buffer[i] == 0)
			return 0;
	}
	return 1;
}

int buffer_vazio() {
	int i;
	for ( i = 0; i < N; i++ ) {
		if (buffer != 0)
			return 0;
	}

	return 1;
}*/

void * produce(void * p) {
	int i;
	int th = (int)(size_t)p;
	for ( i = 0; i < MAX; i++ ) {
		pthread_mutex_lock(&mutex);
		while (pos >= N) {
			// espera buffer liberar
			pthread_cond_wait(&condprod, &mutex);
		}
		buffer[pos] = rand()%100+1;
		printf("Thread %d escrevendo no buffer: %d \\ pos: %d\n", th, buffer[pos], pos);
		pos++;

		pthread_cond_signal(&condcons);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

void * consume(void * p) {
	int i;
	int th = (int)(size_t)p;
	for ( i = 0; i < MAX; i++ ) {
		pthread_mutex_lock(&mutex);
		while (pos <= 0) {
			// espera buffer ter conteúdo
			pthread_cond_wait(&condcons, &mutex);
		}
		int rd = buffer[--pos];
		printf("Thread %d lendo do buffer: %d \\ pos: %d\n", th, rd, pos);

		pthread_cond_signal(&condprod);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}


int main(int argc, char ** argv) {
	N = atoi(argv[1]);

	buffer = (int*)malloc(sizeof(int) * N);

	pthread_t tid[5];
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condprod, NULL);
	pthread_cond_init(&condcons, NULL);

	srand(time(NULL));
	int i;
	for (i = 0; i < 5; i++) {
		if (i % 2 == 0)
			pthread_create(&tid[i], NULL, produce, (void*)(size_t)i);
		else
			pthread_create(&tid[i], NULL, consume, (void*)(size_t)i);
	}

	for ( i = 0; i < 5; i++ )
		pthread_join(tid[i], NULL);
	return 0;
}