#include "functions.h"

void init_data (struct data * Data) {
	cin >> Data->cabecote;
	cin >> Data->fila_espera_size;
	int p;

	Data->fila = (int*) malloc(Data->fila_espera_size * sizeof(int));
	for (int i = 0; i < Data->fila_espera_size; i++) {
		cin >> Data->fila[i];
	}
}

int count_cilindros (struct data Data) {
	int cilindros = 0;
	cilindros += abs(Data.cabecote - Data.fila[0]);
	for (int i = 0; i < Data.fila_espera_size - 1; i++) {
		cilindros += abs(Data.fila[i] - Data.fila[i + 1]);
	}

	return cilindros;
}

void print_data (struct data Data) {
	int cilindros = 0;

	cilindros = count_cilindros(Data);

	cout << "\tOrdem: " << Data.cabecote;
	for (int i = 0; i < Data.fila_espera_size; i++) {
		cout << ", " << Data.fila[i];
	}
	cout << endl;
	cout << "\tCilindros: " << cilindros << endl; 
}

int has_minor (int n, int * data, int len) {
	int ret = 0;
	for (int i = 0; i < len; i++) {
		if (data[i] < 0)
			continue;

		if (data[i] < n) {
			ret = 1;
			break;
		}
	}

	return ret;
}

int has_major (int n, int * data, int len) {
	int ret = 0;
	for (int i = 0; i < len; i++) {
		if (data[i] < 0)
			continue;

		if (data[i] > n) {
			ret = 1;
			break;
		}
	}

	return ret;
}

void print_fcfs (struct data Data) {
	cout << "FCFS" << endl;
	print_data(Data);
}

void print_sstf (struct data Data) {
	cout << "SSTF" << endl;

	int * aux = (int*) malloc(sizeof(int) * Data.fila_espera_size);
	memcpy(aux, Data.fila, Data.fila_espera_size * sizeof(int));

	int min_n = 1000000000;
	int index = 0;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		int n = abs(Data.cabecote - aux[i]);
		if (n < min_n) {
			min_n = n;
			index = i;
		}
	}

	Data.fila[0] = aux[index];
	aux[index] = -1;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		min_n = 1000000000;
		index = -1;
		for (int j = 0; j < Data.fila_espera_size; j++) {
			if (aux[j] == -1)
				continue;

			int n = abs(Data.fila[i] - aux[j]);
			if (n < min_n) {
				min_n = n;
				index = j;
			}
		}
		if (index == -1)
			break;
		Data.fila[i+1] = aux[index];
		aux[index] = -1;
	}


	print_data(Data);
}

void print_scan_desce (struct data Data) {
	cout << "SCAN DESCE" << endl;

	int * aux = (int*) malloc(sizeof(int) * Data.fila_espera_size);
	memcpy(aux, Data.fila, Data.fila_espera_size * sizeof(int));

	int min_n = 100000000;
	int index = 0;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		int n = abs(Data.cabecote - aux[i]);
		int h_m = has_minor(Data.cabecote, Data.fila, Data.fila_espera_size);
		if (h_m&& aux[i] < Data.cabecote) {
			if (min_n > n) {
				min_n = n;
				index = i;
			}
		} else if (!h_m) {
			if (n < min_n) {
				min_n = n;
				index = i;
			}
		}
	}

	Data.fila[0] = aux[index];
	aux[index] = -1;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		int min_n = 1000000000;
		int index = -1;
		for (int j = 0; j < Data.fila_espera_size; j++) {
			if (aux[j] == -1)
				continue;

			int n = abs(Data.fila[i] - aux[j]);
			int h_m = has_minor(Data.fila[i], aux, Data.fila_espera_size);
			if (h_m && aux[j] < Data.fila[i]) {
				if (min_n > n) {
					min_n = n;
					index = j;
				}
			} else if (!h_m) {
				if (n < min_n) {
					min_n = n;
					index = j;
				}
			}
		}

		if (index == -1)
			break;

		Data.fila[i+1] = aux[index];
		aux[index] = -1;
	}

	print_data(Data);
}

void print_scan_sobe (struct data Data) {
	cout << "SCAN SOBE" << endl;
	int * aux = (int*) malloc(sizeof(int) * Data.fila_espera_size);
	memcpy(aux, Data.fila, Data.fila_espera_size * sizeof(int));

	int min_n = 100000000;
	int index = 0;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		int n = abs(Data.cabecote - aux[i]);
		int h_m = has_major(Data.cabecote, Data.fila, Data.fila_espera_size);
		if (h_m && aux[i] > Data.cabecote) {
			if (min_n > n) {
				min_n = n;
				index = i;
			}
		} else if (!h_m) {
			if (n < min_n) {
				min_n = n;
				index = i;
			}
		}
	}

	Data.fila[0] = aux[index];
	aux[index] = -1;

	for (int i = 0; i < Data.fila_espera_size; i++) {
		int min_n = 1000000000;
		int index = -1;
		for (int j = 0; j < Data.fila_espera_size; j++) {
			if (aux[j] == -1)
				continue;

			int n = abs(Data.fila[i] - aux[j]);
			int h_m = has_major(Data.fila[i], aux, Data.fila_espera_size);
			if (h_m && aux[j] > Data.fila[i]) {
				if (min_n > n) {
					min_n = n;
					index = j;
				}
			} else if (!h_m) {
				if (n < min_n) {
					min_n = n;
					index = j;
				}
			}
		}

		if (index == -1)
			break;

		Data.fila[i+1] = aux[index];
		aux[index] = -1;
	}

	print_data(Data);
}