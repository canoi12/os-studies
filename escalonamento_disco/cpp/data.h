#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class Data {
private:
	int cabecote;
	int size;
	int * fila;

	int * lista;

	int index;

	/** 
		Conta a quantidade de cilindros lidos

		@return Número de cilíndros
	**/
	int countCilindros();

	/**
		Checa se existe algum número menor que o que está sendo testado atualmente na fila

		@param o vetor auxiliar usando em outras funções
		@return um booleano que diz se tem algum número menor ou não
	**/
	bool hasMinor(int * aux);

	/**
		Checa se existe algum número maior que o que está sendo testado atualmente na fila

		@param o vetor auxiliar usando em outras funções
		@return um booleano que diz se tem algum número maior ou não
	**/
	bool hasMajor(int * aux);

	// Reseta a lista
	void resetList();

	// Printa a lista na ordem e a quantidade de cilindros lidos
	void print();
public:
	Data();
	Data(int cabecote, int size, int * fila);
	~Data();

	// Imprime a ordem e a quantidade de cilindros percorridos usando o algoritmo FCFS
	void FCFS();

	// Imprime a ordem e a quantidade de cilindros percorridos usando o algoritmo SSTF
	void SSTF();

	// Imprime a ordem e a quantidade de cilindros percorridos usando o algoritmo SCAN SOBE
	void SCAN_SOBE();

	// Imprime a ordem e a quantidade de cilindros percorridos usando o algoritmo SCAN DESCE
	void SCAN_DESCE();

};