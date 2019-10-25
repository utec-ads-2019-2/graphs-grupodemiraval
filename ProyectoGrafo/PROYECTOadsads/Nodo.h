#ifndef PROYECTOGRAFO_NODO_H
#define PROYECTOGRAFO_NODO_H
#include "Arista.h"
#include <vector>

template <typename T1>
class Nodo {
public:
	T1 data;
	float posx, posy;
	std::vector<Arista<T1>*> aristas;
	Nodo(T1 data) :data{ data }
	{
		posx = data->Longitud;
		posy = data->Latitud;
	}

	void Imprimir_Aristas()
	{
		std::cout << "Aristas del nodo: " << this->data->id << "\n";
		for (auto it : this->aristas)
		{
			std::cout << "Origen: " << it->nodos[0]->data->id << " / " << "Final: " << it->nodos[1]->data->id << "\n";
		}
	}
};


#endif //PROYECTOGRAFO_NODO_H