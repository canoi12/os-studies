#include "data.h"

Data * init_data () {
	Data * data = (Data*) calloc(1, sizeof(Data));

	scanf("%d", &(data->cabecote));
	scanf("%d", &(data->size));

	data->fila = (int*) malloc(data->size * sizeof(int));
	data->lista = (int*) malloc((data->size + 1) * sizeof(int));

	data->lista[0] = data->cabecote;

	for (int i = 0; i < data->size; i++) {
		scanf("%d", &(data->fila[i]));
		data->lista[i+1] = data->fila[i];
	}

	return data;
}

void reset_lista (Data * data) {
	data->lista[0] = data->cabecote;

	for (int i = 0; i < data->size; i++)
		data->lista[i + 1] = data->fila[i];
}

int count_cilindros (Data * data) {
	int cilindros = 0;
	for (int i = 0; i < data->size; i++) {
		cilindros += abs(data->lista[i] - data->lista[i + 1]);
	}

	return cilindros;
}

int has_minor (Data * data, int * aux) {
	int ret = 0;
	for (int i = 0; i < data->size; i++) {
		if (aux[i] < 0)
			continue;

		if (data->lista[data->index] > aux[i]) {
			ret = 1;
			break;
		}
	}

	return ret;
}

int has_major (Data * data, int * aux) {
	int ret = 0;
	for (int i = 0; i < data->size; i++) {
		if (aux[i] < 0)
			continue;

		if (data->lista[data->index] < aux[i]) {
			ret = 1;
			break;
		}
	}

	return ret;
}

void print_data (Data * data) {
	printf("\tOrdem: ");
	for (int i = 0; i < data->size + 1; i++) {
		printf("%d", data->lista[i]);
		if (i < data->size)
			printf(", ");
	}

	printf("\n");

	printf("\tCilindros: %d\n", count_cilindros(data));
}

void print_fcfs (Data * data) {
	printf("FCFS\n");

	print_data(data);
}

void print_sstf (Data * data) {
	printf("SSTF\n");

	int * aux = malloc(sizeof(int) * data->size);
	memcpy(aux, data->fila, data->size * sizeof(int));

	reset_lista(data);

	for (int i = 0; i < data->size; i++) {
		int min_n = 201;
		int index = -1;
		for (int j = 0; j < data->size; j++) {
			if (aux[j] < 0)
				continue;

			int n = abs(data->lista[i] - aux[j]);
			if (min_n > n) {
				min_n = n;
				index = j;
			}
		}
		if (index < 0)
			break;

		data->lista[i + 1] = aux[index];
		aux[index] = -1;
	}

	print_data(data);
}

void print_scan_desce (Data * data) {
	printf("SCAN DESCE\n");

	int * aux = (int*)malloc(sizeof(int) * data->size);
	memcpy(aux, data->fila, sizeof(int) * data->size);

	reset_lista(data);

	for (int i = 0; i < data->size; i++) {
		int min_n = 201;
		int index = -1;
		data->index = i;
		for (int j = 0; j < data->size; j++) {
			if (aux[j] < 0)
				continue;
			int n = abs(data->lista[i] - aux[j]);
			if (has_minor(data, aux)) {
				if (data->lista[i] > aux[j]) {
					if (min_n > n) {
						min_n = n;
						index = j;
					}
				}
			} else {
				if (min_n > n) {
						min_n = n;
						index = j;
					}
			}
		}

		if (index < 0)
			break;

		data->lista[i + 1] = aux[index];
		aux[index] = -1;
	}

	print_data(data);
}

void print_scan_sobe (Data * data) {
	printf("SCAN SOBE\n");


	int * aux = (int*)malloc(sizeof(int) * data->size);
	memcpy(aux, data->fila, sizeof(int) * data->size);

	reset_lista(data);

	for (int i = 0; i < data->size; i++) {
		int min_n = 201;
		int index = -1;
		data->index = i;
		for (int j = 0; j < data->size; j++) {
			if (aux[j] < 0)
				continue;
			int n = abs(data->lista[i] - aux[j]);
			if (has_major(data, aux)) {
				if (data->lista[i] < aux[j]) {
					if (min_n > n) {
						min_n = n;
						index = j;
					}
				}
			} else {
				if (min_n > n) {
						min_n = n;
						index = j;
					}
			}
		}

		if (index < 0)
			break;

		data->lista[i + 1] = aux[index];
		aux[index] = -1;
	}


	print_data(data);
}