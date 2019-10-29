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

	Arista<T1>* menor_Arista() {
		int min = aristas.front.peso;
		auto menor_arista = aristas.front();
		for (auto it : aristas) {
			if (it.peso > min) {
				menor_arista = min;
			}
		}

		return menor_arista;
	}


	void insertar(Arista<T1>* arista) {
		if (!aristas.empty()) {
			for (auto in = aristas.begin(); in != aristas.end(); ++in) {
				if (arista->nodos[0] == (*in)->nodos[1] && arista->nodos[1] == (*in)->nodos[0]) {

				}
				else {
					aristas.push_back(arista);
				}
			}
		}
		else {
			aristas.push_back(arista);
		}
		
	}
};


#endif //PROYECTOGRAFO_NODO_H