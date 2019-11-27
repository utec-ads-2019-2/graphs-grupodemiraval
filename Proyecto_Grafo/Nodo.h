#ifndef PROYECTOGRAFO_NODO_H
#define PROYECTOGRAFO_NODO_H
#include "Arista.h"
#include <vector>
#include <iostream>

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

	bool seRepite(Arista<T1>* arista) {
		if (!aristas.empty()) {
			for (auto it : aristas) {
				if (it->nodos[0] == arista->nodos[0] && it->nodos[1] == arista->nodos[1]) { return true; }
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}

	T1 getData() {
		return data;
	}

	vector<Arista<T1>*> getEdges() {
		return aristas;
	}
};


#endif //PROYECTOGRAFO_NODO_H
