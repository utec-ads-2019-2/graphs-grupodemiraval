#ifndef PROYECTOGRAFO_GRAFO_H
#define PROYECTOGRAFO_GRAFO_H

#include <vector>
#include "Nodo.h"

using namespace std;
template<typename T1>
class Grafo {
public:
    vector<Nodo<T1>*> nodos;
    Grafo()=default;
    void Insertar_Nodo(T1 data);
    void Generar_Aristas();
    void Imprimir_Grafo();
    Nodo<T1>* Buscar_Nodo(int search_id);
    Nodo<T1>* Buscar_Nodo(int search_id, int &pos);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final, int &pos);
    void Remover_Arista(int id_inicio, int id_final);
    void Remover_Nodo(int remove_id);

	
};

template <typename T1>
void Grafo<T1>::Insertar_Nodo(T1 data)
{
    auto temp = new Nodo<T1>(data);
    this->nodos.push_back(temp);
}

template <typename T1>
Nodo<T1>* Grafo<T1>::Buscar_Nodo(int search_id)
{
    for(auto it : this->nodos)
    {
        if(it->data->id==search_id)
        {
            return it;
        }
    }
    return nullptr;
}

template <typename T1>
Nodo<T1>* Grafo<T1>::Buscar_Nodo(int search_id,int &pos)
{
    for(auto it : this->nodos)
    {
        if(it->data->id==search_id)
        {
            return it;
        }
        pos++;
    }
    return nullptr;
}

template <typename T1>
Arista<T1>* Grafo<T1>::Buscar_Arista(int id_inicio, int id_final)
{
    for(auto node : this->nodos)
    {
        if(node->data->id==id_inicio)
        {
            for(auto aris : node->aristas)
            {
                if(aris->nodos[1]->data->id == id_final)
                {
                    return aris;
                }
            }
            return nullptr;
        }
    }
    return nullptr;
}

template <typename T1>
Arista<T1>* Grafo<T1>::Buscar_Arista(int id_inicio, int id_final, int &pos)
{
    for(auto node : this->nodos)
    {
        pos = 0;
        if(node->data->id==id_inicio)
        {
            for(auto aris : node->aristas)
            {
                if(aris->nodos[1]->data->id == id_final)
                {
                    return aris;
                }
                pos++;
            }
            return nullptr;
        }
    }
    return nullptr;
}

template <typename T1>
void Grafo<T1>::Generar_Aristas()
{
    for(auto it : this->nodos)
    {
        for(auto dest : it->data->destinos )
        {
            auto destino = Buscar_Nodo(dest);
			if (destino != nullptr) {
				auto aux = new Arista<T1>(it, destino);
				it->aristas.push_back(aux);
			}
        }
    }
}

template <typename T1>
void Grafo<T1>::Imprimir_Grafo()
{
	for (auto it : this->nodos)
	{
		it->Imprimir_Aristas();
	}
}

template<typename T1>
void Grafo<T1>::Remover_Arista(int id_inicio, int id_final)
{
    int pos = 0;
    auto arist = Buscar_Arista(id_inicio,id_final,pos);
    auto nodo = arist->nodos[0];
    nodo->aristas.erase(nodo->aristas.begin()+pos);
    delete arist;
}

template<typename T1>
void Grafo<T1>::Remover_Nodo(int remove_id) {
    int pos = 0;
    auto node = Buscar_Nodo(remove_id,pos);
    this->nodos.erase(this->nodos.begin()+pos);
    for(auto it : this->nodos)
    {
        pos = 0;
        for(auto aris : it->aristas)
        {
            if(aris->nodos[1] == node)
            {
                it->aristas.erase(it->aristas.begin()+pos);
                delete aris;
                break;
            }
            pos++;
        }
    }
    delete node;
}


class Aeropuerto {
public:
	string Ciudad;
	string Nombre;
	string Pais;
	float Longitud;
	float Latitud;
	int id;
	vector <int> destinos;

	Aeropuerto(string Ciudad, string Nombre, string Pais, float Longitud, float Latitud, int id, vector<int> destinos) :
		Ciudad{ Ciudad }, Nombre{ Nombre }, Pais{ Pais }, Longitud{ Longitud }, Latitud{ Latitud }, id{ id }, destinos{ destinos }{}
};

#endif //PROYECTOGRAFO_GRAFO_H