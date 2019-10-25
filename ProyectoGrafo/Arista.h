#ifndef PROYECTOGRAFO_ARISTA_H
#define PROYECTOGRAFO_ARISTA_H

#include <math.h>

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
};


#endif //PROYECTOGRAFO_ARISTA_H