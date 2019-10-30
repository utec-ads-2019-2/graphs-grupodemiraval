#ifndef PROYECTOGRAFO_GRAFO_H
#define PROYECTOGRAFO_GRAFO_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_set>
#include "Nodo.h"
#include <algorithm>

using namespace std;
template<typename T1>
class Grafo {
public:
    vector<Nodo<T1>*> nodos;
    Grafo()=default;
    void Insertar_Nodo(T1 data);
    void Insertar_Nodo(Nodo<T1>* nodo);
    void Generar_Aristas();
    void Generar_Aristas_noDirec();
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
    Grafo<T1> MST_Kruskal();
};

template <typename T1>
void Grafo<T1>::Generar_Aristas_noDirec()
{
	for (auto it : this->nodos)
	{
		for (auto dest : it->data->destinos)
		{
			auto destino = Buscar_Nodo(dest);
			if (destino != nullptr) {
				auto aux = new Arista<T1>(it, destino);
				it->aristas.push_back(aux);
				if (!destino->seRepite(aux)) {
					destino->aristas.push_back(aux);
				}
			}
		}
	}
}

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
    cout << "antes del dfs " << actual << endl;
    unordered_set<Nodo<T1>*> vis1,vis2;
    this->DFS(actual,vis1);
    cout << "despues de dfs " << actual << endl;
    Grafo<T1> invertido = this->Invertir_Aristas();
    invertido.DFS(actual, vis2);
    for(auto nodo : this->nodos) {
        if(!vis1.count(nodo) && !vis2.count(nodo))
            return false;
    }
    return true;
}

int Buscar_Padre(int id_nodo, map<int,int> padres)
{
  if(padres[id_nodo]==id_nodo)
  {
    return id_nodo;
  }
  return Buscar_Padre(padres[id_nodo],padres);
}

template<typename T1>
bool menor(Arista<T1>* a, Arista<T1>* b)
{
  return a->peso < b->peso;
}

template<typename T1>
Grafo<T1> Grafo<T1>::MST_Kruskal()
{
  vector<Arista<T1>*> Krusk={};
  vector<Arista<T1>*> Aristas_Ordenadas;
  map<int,int> padres;
  for(auto node : this->nodos)
  {
    padres[node->data->id]=node->data->id;
    for(auto ar : node->aristas)
    {
        Aristas_Ordenadas.push_back(ar);
    }
  }

  sort(Aristas_Ordenadas.begin(),Aristas_Ordenadas.end(),menor<T1>);
  int i = 0;
  while(Krusk.size()<this->nodos.size()-1)
  {
    Arista<T1>* actual = Aristas_Ordenadas[i];
    int padre_inicio = Buscar_Padre(actual->nodos[0]->data->id,padres);
    int padre_final = Buscar_Padre(actual->nodos[1]->data->id,padres);
    if(padre_inicio!=padre_final)
    {
      Krusk.push_back(actual);
      padres[padre_inicio]=padre_final;
    }
    i++;
  }
  Grafo<T1> MST_graph;
  for(auto cc : Krusk)
  {
    cc->nodos[0]->aristas.clear();
    cc->nodos[1]->aristas.clear();
  }
  for(auto it : Krusk)
  {
    if(MST_graph.Buscar_Nodo(it->nodos[0]->data->id)==nullptr)
    {
      MST_graph.nodos.push_back(it->nodos[0]);
    }
    if(MST_graph.Buscar_Nodo(it->nodos[1]->data->id)==nullptr)
    {
      MST_graph.nodos.push_back(it->nodos[1]);
    }
    it->nodos[0]->aristas.push_back(it);
    it->nodos[1]->aristas.push_back(it);
  }
  return MST_graph;
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
