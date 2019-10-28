#ifndef PROYECTOGRAFO_GRAFO_H
#define PROYECTOGRAFO_GRAFO_H

#include <vector>
#include <map>
#include <queue>
#include <unordered_set>
#include "Nodo.h"

using namespace std;
template<typename T1>
class Grafo {
public:
    vector<Nodo<T1>*> nodos;
    Grafo()=default;
    void Insertar_Nodo(T1 data);
    void Insertar_Nodo(Nodo<T1>* nodo);
    void Generar_Aristas();
    void Imprimir_Grafo();
    Nodo<T1>* Buscar_Nodo(int search_id);
    Nodo<T1>* Buscar_Nodo(int search_id, int &pos);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final, int &pos);
    void Remover_Arista(int id_inicio, int id_final);
    void Remover_Nodo(int remove_id);
    bool Es_Bipartito();
	bool Es_Conexo();
    void DFS(Nodo<T1>*& v, unordered_set<Nodo<T1>*>& visited);
    void Generar_Aristas_Invertidas();
    Grafo<T1> Invertir_Aristas();
};

template <typename T1>
void Grafo<T1>::Insertar_Nodo(T1 data)
{
    auto temp = new Nodo<T1>(data);
    this->nodos.push_back(temp);
}

template<typename T1>
void Grafo<T1>::Insertar_Nodo(Nodo<T1>* nodo) {
    this->nodos.push_back(nodo);
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
void Grafo<T1>::Generar_Aristas_Invertidas()
{
    for(auto it : this->nodos)
    {
        for(auto dest : it->data->destinos )
        {
            auto destino = Buscar_Nodo(dest);
			if (destino != nullptr) {
				auto aux = new Arista<T1>(destino, it);
				destino->aristas.push_back(aux);
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

template<typename T1>
bool Grafo<T1>::Es_Bipartito() {
    map<int,bool> colores;
    unordered_set<Nodo<T1>*> sin_colorear;
    for(auto n : this->nodos)
        sin_colorear.insert(n);
    colores[this->nodos[0]->data->id] = true;
    sin_colorear.erase(this->nodos[0]);
    queue<Nodo<T1>*> q;
    q.push(this->nodos[0]);
    while(!q.empty()) {
        Nodo<T1>* actual = q.front();
        q.pop();
        for(auto arista : actual->aristas) {
            Nodo<T1>* vecino = arista->nodos[1];
            if(!colores.count(vecino->data->id)) {
                colores[vecino->data->id] = !colores[actual->data->id];
                sin_colorear.erase(vecino);
                q.push(vecino);
            }
            else if(colores[vecino->data->id] == colores[actual->data->id])
                return false;
        }
        if(q.empty() && !sin_colorear.empty()) {
            auto nodo = *sin_colorear.begin();
            colores[nodo->data->id] = true;
            sin_colorear.erase(nodo);
            q.push(nodo);
        }
    }
    return true;
}

template<typename T1>
Grafo<T1> Grafo<T1>::Invertir_Aristas() {
    Grafo<T1> graph;
    for(auto nodo : this->nodos) {
        graph.Insertar_Nodo(nodo);
        graph.Generar_Aristas_Invertidas();
    }
    return graph;
}

template<typename T1>
void Grafo<T1>::DFS(Nodo<T1>*& v, unordered_set<Nodo<T1>*>& visited) {
    visited.insert(v);
    for(auto arista : v->aristas) {
        if(!visited.count(arista->nodos[1])) {
            v = arista->nodos[1];
            DFS(v, visited);
        }
    }
}

template<typename T1>
bool Grafo<T1>::Es_Conexo() {
    Nodo<T1>* actual = this->nodos[0];
    unordered_set<Nodo<T1>*> vis1,vis2;
    this->DFS(actual,vis1);
    Grafo<T1> invertido = this->Invertir_Aristas();
    invertido.DFS(actual, vis2);
    for(auto nodo : this->nodos) {
        if(!vis1.count(nodo) && !vis2.count(nodo))
            return false;
    }
    return true;
}

template<typename T1>
bool Grafo<T1>::Es_Fuertemente_Conexo() {
    Nodo<T1>* inicio = this->nodos[0];
    unordered_set<Nodo<T1>*>vis1,vis2;
    this->DFS(inicio,vis1);
    if(this->nodos.size() != vis1.size())
        return false;
    Grafo<T1> invertido = this->Invertir_Aristas();
    inicio = this->nodos[0];
    invertido.DFS(actual, vis2);
    if(this->nodos.size() != vis2.size())
        return false;
    return true;
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