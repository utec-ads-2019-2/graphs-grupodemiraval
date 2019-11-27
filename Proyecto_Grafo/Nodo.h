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

	Arista<T1>* isAdyacent(Nodo<T1>* nodo) {
		for (auto c : aristas) {
			if (c->nodos[0]->data->id == nodo->data->id || c->nodos[1]->data->id == nodo->data->id) {
				return c;
			}
		}
		return nullptr;
	};

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
		return false;
	}
};


#endif //PROYECTOGRAFO_NODO_H