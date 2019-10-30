#ifndef PROYECTOGRAFO_ARISTA_H
#define PROYECTOGRAFO_ARISTA_H

#include <math.h>
#include<iostream>

using namespace std;

template <typename T1>
class Nodo;

template <typename T1>
class Arista {
public:
	float peso;
	Nodo<T1>* nodos[2];
	Arista(Nodo<T1>* inicio, Nodo<T1>* final)
	{
		nodos[0] = inicio;
		nodos[1] = final;
		peso = sqrt(pow(inicio->posx - final->posx, 2) + pow(inicio->posy - final->posy, 2));
	}
	Arista()=default;
	void Imprimir()
	{
		cout<<nodos[0]->data->id<<" "<<nodos[1]->data->id<<" "<<peso<<endl;
	}
};


#endif //PROYECTOGRAFO_ARISTA_H
