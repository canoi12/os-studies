#ifndef __DATA__
#define __DATA__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
	int cabecote;
	int size;
	int * fila;
	int * lista;

	int index;

} Data;

Data * init_data();

void reset_lista (Data * data);

int count_cilindros (Data * data);

void print_data (Data * data);

int has_minor (Data * data, int * aux);

int has_major (Data * data, int * aux);

void print_fcfs (Data * data);

void print_sstf (Data * data);

void print_scan_sobe (Data * data);

void print_scan_desce (Data * data);

#endif