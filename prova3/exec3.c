#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX 100000
int base_dados = 0;
pthread_mutex_t mutex;
int nL, nG;

void * le_base_dados(void * p) {
	int i;
	int th = (int)(size_t)p;
	for ( i = 0; i < MAX; i++ ) {
		printf("Leitor %d lendo dado %d\n", th, base_dados);
		sleep(1);
	}

	pthread_exit(NULL);
}

void * grava_base_dados(void * p) {
	int i;
	int th = (int)(size_t)p;
	for ( i = 0; i < MAX; i++ ) {
		pthread_mutex_lock(&mutex);
		base_dados++;
		printf("Escritor %d escrevendo dado %d\n", th, base_dados);
		
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

	pthread_exit(NULL);
}

int main (int argc, char ** argv ) {

	nL = atoi(argv[1]);
	nG = atoi(argv[2]);
	pthread_t leitor[nL];
	pthread_t escritor[nG];
	pthread_mutex_init(&mutex, NULL);
	printf("GRAVADORES %d\n", nG);
	srand(time(NULL));
	int i;
	for (i = 0; i < nL; i++)
			pthread_create(&leitor[i], NULL, le_base_dados, (void*)(size_t)i);
	for (i = 0; i < nG; i++)
			pthread_create(&escritor[i], NULL, grava_base_dados, (void*)(size_t)i);

	for (i = 0; i < nL; i++)
			pthread_join(leitor[i], NULL);
	for (i = 0; i < nG; i++)
			pthread_join(escritor[i], NULL);

	return 0;
}