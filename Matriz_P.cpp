#include "Matriz_P.hpp"

int **CrearMatriz(unsigned int nFilas, unsigned int nCol){
	int **Puntero_Matriz=0;
	Puntero_Matriz=new int*[nFilas]; //reservando memoria para las filas

	for(unsigned int i=0 ; i<nFilas ; i++)
		Puntero_Matriz[i]=new int[nCol];//reservar memoria para las columnas

	return Puntero_Matriz;
}

void LiberarMemoria(int **Puntero_Matriz, unsigned int nFilas, unsigned int nCol){
	for(unsigned int i=0 ; i<nFilas ; i++)
		delete[] Puntero_Matriz[i];//reservar memoria para las columnas

	delete Puntero_Matriz;
}


float **CrearMatrizfloat(unsigned int nFilas, unsigned int nCol){
	float **Puntero_Matriz=0;
	Puntero_Matriz=new float*[nFilas]; //reservando memoria para las filas

	for(unsigned int i=0 ; i<nFilas ; i++)
		Puntero_Matriz[i]=new float[nCol];//reservar memoria para las columnas

	return Puntero_Matriz;
}

void LiberarMemoriafloat(float **Puntero_Matriz, unsigned int nFilas, unsigned int nCol){

	for(unsigned int i=0 ; i<nFilas ; i++)
		delete[] Puntero_Matriz[i];//reservar memoria para las columnas

	delete Puntero_Matriz;
}
