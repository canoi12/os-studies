#include "data.h"

Data::Data() {
	cin >> this->cabecote;
	cin >> this->size;

	this->fila = new int[this->size];
	for (int i = 0; i < this->size; i++) 
		cin >> this->fila[i];

	this->lista = new int[this->size + 1];

	index = 0;
}

Data::Data(int cabecote, int size, int * fila) {
	this->cabecote = cabecote;
	this->size = size;
	this->fila = fila;

	this->lista = new int[this->size + 1];

	index = 0;
}

Data::~Data() {
	delete(this->fila);
	delete(this->lista);

}

int Data::countCilindros() {
	int cilindros = 0;

	for (int i = 0; i < this->size; i++) {
		cilindros += abs(this->lista[i] - this->lista[i + 1]);
	}

	return cilindros;
}

bool Data::hasMinor(int * aux) {
	bool ret = false;

	for (int i = 0; i < this->size; i++) {
		if (aux[i] < 0)
			continue;

		if (this->lista[this->index] > aux[i]) {
			ret = true;
			break;
		}
	}

	return ret;
}

bool Data::hasMajor(int * aux) {
	bool ret = false;

	for (int i = 0; i < this->size; i++) {
		if (aux[i] < 0)
			continue;

		if (this->fila[index] < aux[i]) {
			ret = true;
			break;
		}
	}

	return ret;
}

void Data::resetList() {
	this->lista[0] = this->cabecote;

	for (int i = 0; i < this->size; i++) {
		this->lista[i+1] = this->fila[i];
	}
}

void Data::print() {
	cout << "\tOrdem: ";
	for (int i = 0; i < this->size + 1; i++) {
		cout << this->lista[i];
		if (i < this->size)
			cout << ", ";
	}
	cout << endl;
	cout << "\tCilindros: " << this->countCilindros() << endl; 
}

void Data::FCFS() {
	cout << "FCFS" << endl;

	this->resetList();

	this->print();
}

void Data::SSTF() {
	cout << "SSTF" << endl;

	this->resetList();

	int * aux = new int[this->size];
	memcpy(aux, this->fila, this->size * sizeof(int));

	int min_n = 201;
	int index = 0;

	for (int i = 0; i < this->size + 1; i++) {
		min_n = 201;
		index = -1;
		for (int j = 0; j < this->size; j++) {
			if (aux[j] < 0)
				continue;

			int n = abs(this->lista[i] - aux[j]);
			if (n < min_n) {
				min_n = n;
				index = j;
			}
		}
		this->lista[i + 1] = aux[index];
		aux[index] = -1;
	}

	this->print();
}

void Data::SCAN_DESCE() {
	cout << "SCAN DESCE" << endl;

	int * aux = new int[this->size];
	memcpy(aux, this->fila, this->size * sizeof(int));

	int min_n = 201;
	int index = 0;

	for (int i = 0; i < this->size + 1; i++) {
		min_n = 201;
		index = -1;
		this->index = i;
		for (int j = 0; j < this->size; j++) {
			if (aux[j] < 0)
				continue;

			if(this->hasMinor(aux)) {
				if (this->lista[i] > aux[j]) {
					int n = abs(this->lista[i] - aux[j]);
					if (n < min_n) {
						min_n = n;
						index = j;
					}
				}
			} else {
				int n = abs(this->lista[i] - aux[j]);
				if (n < min_n) {
					min_n = n;
					index = j;
				}
			}
		}

		if (index < 0)
			break;

		this->lista[i + 1] = aux[index];
		aux[index] = -1;
	}

	this->print();
}

void Data::SCAN_SOBE() {
	cout << "SCAN SOBE" << endl;

	int * aux = new int[this->size];
	memcpy(aux, this->fila, this->size * sizeof(int));

	int min_n = 201;
	int index = 0;

	for (int i = 0; i < this->size + 1; i++) {
		min_n = 201;
		index = -1;
		this->index = i;
		for (int j = 0; j < this->size; j++) {
			if (aux[j] < 0)
				continue;

			if(this->hasMajor(aux)) {
				if (this->lista[i] < aux[j]) {
					int n = abs(this->lista[i] - aux[j]);
					if (n < min_n) {
						min_n = n;
						index = j;
					}
				}
			} else {
				int n = abs(this->lista[i] - aux[j]);
				if (n < min_n) {
					min_n = n;
					index = j;
				}
			}
		}

		if (index < 0)
			break;

		this->lista[i + 1] = aux[index];
		aux[index] = -1;
	}

	this->print();
}