#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int ** matriz1;
int ** matriz2;
int ** matrizR;
int M = 0;
pthread_mutex_t mutex;

void printaMatriz(int ** matriz);

void * multiplicaMatriz(void * p) {
	int i, j, n;
	int sum = 0;

	int linha = (int)(size_t)p;

	pthread_mutex_lock(&mutex);

	for (i = 0; i < M; i++) {
		sum = 0;
		for (j = 0; j < M; j++)
			sum += matriz1[linha][j] * matriz2[j][i];
		matrizR[linha][i] = sum;
	}

	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void printaMatriz(int ** matriz) {
	int i,j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < M; j++) {
			printf("%d\t", matriz[i][j]);
		}

		printf("\n");
	}
}

int main(int argc, char ** argv) {
	M = atoi(argv[1]);
	int i, j;
	pthread_t tid[M];
	pthread_mutex_init(&mutex, NULL);

	srand(time(NULL));

	matriz1 = (int**)malloc(sizeof(int *) * M);
	matriz2 = (int**)malloc(sizeof(int *) * M);
	matrizR = (int**)malloc(sizeof(int *) * M);

	for (i = 0; i < M; i++) {
		matriz1[i] = (int*)calloc(M, sizeof(int));
		matriz2[i] = (int*)calloc(M, sizeof(int));
		matrizR[i] = (int*)calloc(M, sizeof(int));
		for (j = 0; j < M; j++) {
			matriz1[i][j] = rand()%100;
			matriz2[i][j] = rand()%100;
			matrizR[i][j] = 0;
		}
	}

	for (i = 0; i < M; i++)
		pthread_create(&tid[i], NULL, multiplicaMatriz, (void*)(size_t)i);

	for (i = 0; i < M; i++)
		pthread_join(tid[i], NULL);

	printf("Matriz 1:\n");
	printaMatriz(matriz1);
	printf("Matriz 2:\n");
	printaMatriz(matriz2);
	printf("Matriz R:\n");
	printaMatriz(matrizR);

	return 0;
}