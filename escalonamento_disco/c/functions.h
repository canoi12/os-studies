#include <iostream>
#include <cstring>
using namespace std;

#ifndef __FUNCTIONS__
#define __FUNCTIONS__

struct data {
	int cabecote;
	int fila_espera_size;
	int * fila;
};

void init_data (struct data * Data);

int count_cilindros (struct data Data);

void print_data (struct data Data);

int has_minor (int n, int * data);

int has_major (int n, int * data);

void print_fcfs (struct data Data);

void print_sstf (struct data Data);

void print_scan_desce (struct data Data);

void print_scan_sobe (struct data Data);

#endif