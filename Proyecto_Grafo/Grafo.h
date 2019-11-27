#ifndef PROYECTOGRAFO_GRAFO_H
#define PROYECTOGRAFO_GRAFO_H

#include <vector>
#include <map>
#include <queue>
#include <unordered_set>
#include "Nodo.h"
#include <algorithm>
#include <limits>

using namespace std;
template<typename T1>
class Grafo {
public:
    vector<Nodo<T1>*> nodos;
    Grafo()=default;
    ~Grafo()
    {
      for(auto cc : this->nodos)
      {
        Remover_Nodo(cc->data->id);
      }
      delete this;
    }
    void Insertar_Nodo(T1 data);
    virtual void Generar_Aristas() = 0;
    virtual void Ejecutar() = 0;
    void Imprimir_Grafo();
    Nodo<T1>* Buscar_Nodo(int search_id);
    Nodo<T1>* Buscar_Nodo(int search_id, int &pos);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final);
    Arista<T1>* Buscar_Arista(int id_inicio, int id_final, int &pos);
    virtual void Remover_Arista(int id_inicio, int id_final) = 0;
    void Remover_Nodo(int remove_id);
    bool Es_Bipartito();
    virtual double Densidad(double cota) = 0;
	bool Es_Conexo();
    void DFS(Nodo<T1>*& v, unordered_set<int>& visited);
    void Generar_Aristas_Invertidas();
    Grafo<T1>* Invertir_Aristas();
    bool Es_Fuertemente_Conexo();
    int Get_aristas();
	Arista<T1>* menor_Arista(vector<Nodo<T1>*>* vectorcito);
  pair<map<Nodo<T1>*,map<Nodo<T1>*,float> >,map<Nodo<T1>*,map<Nodo<T1>*,Nodo<T1>*> > > FloydWarshall();
  unordered_map<int, Graph<T1>* > BellmanFord(int inicio);
};


template<typename T1>
class Grafo_dirigido : public Grafo<T1> {
public:
	void Generar_Aristas() override {
		for (auto it : this->nodos)
		{
			for (auto dest : it->data->destinos)
			{
				auto destino = this->Buscar_Nodo(dest);
				if (destino != nullptr) {
					auto aux = new Arista<T1>(it, destino);
					it->aristas.push_back(aux);
				}
			}
		}
	}
  void Remover_Arista(int id_inicio, int id_final) override
  {
    int pos = 0;
    auto arist = this->Buscar_Arista(id_inicio,id_final,pos);
    auto nodo = arist->nodos[0];
    nodo->aristas.erase(nodo->aristas.begin()+pos);
    delete arist;
  }
  void Ejecutar() override {};
  double Densidad(double cota) override
  {
    double num_aristas = this->Get_aristas();
    double num_nodos = this->nodos.size();
    double densidad = num_aristas/(num_nodos*(num_nodos-1));
    cout<<"Para la cota definida: "<<cota<<endl;
    if(densidad <= cota)
    {
      cout<<"El grafo es disperso con una densidad de "<<densidad<<endl;
    }
    else
    {
      cout<<"El grafo es denso con una densidad de "<<densidad<<endl;
    }
    return densidad;
  }
};

template<typename T1>
class Grafo_no_dirigido : public Grafo<T1> {

public:
	void Generar_Aristas() override {
		for (auto it : this->nodos)
		{
			for (auto dest : it->data->destinos)
			{
				auto destino = this->Buscar_Nodo(dest);
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
  void Remover_Arista(int id_inicio, int id_final) override
  {
    int pos = 0;
    auto arist = this->Buscar_Arista(id_inicio,id_final,pos);
    auto nodo = arist->nodos[0];
    nodo->aristas.erase(nodo->aristas.begin()+pos);
    nodo = arist->nodos[1];
    nodo->aristas.erase(nodo->aristas.begin()+pos);
    delete arist;
  }
  Grafo<T1>* Prim();
  Grafo<T1>* MST_Kruskal();
  void Ejecutar() override
  {

  		cout << "Ejecutando el MST : PRIM : " << endl;

  		auto min_prim = Prim();

      for (auto i : min_prim->nodos)
  		{
  			i->Imprimir_Aristas();
  		}
      cout << "\n\n";



  		cout << "Ejecutando el MST : KRUSKAL : " << endl;

  		auto a = MST_Kruskal();
  		for (auto i : a->nodos)
  		{
  			i->Imprimir_Aristas();
  		}
  }
  double Densidad(double cota) override
  {
    double num_aristas = this->Get_aristas();
    double num_nodos = this->nodos.size();
    double densidad = num_aristas/(2*(num_nodos*(num_nodos-1)));
    cout<<"Para la cota definida: "<<cota<<endl;
    if(densidad <= cota)
    {
      cout<<"El grafo es disperso con una densidad de "<<densidad<<endl;
    }
    else
    {
      cout<<"El grafo es denso con una densidad de "<<densidad<<endl;
    }
    return densidad;
  }
};
template<typename T1>
int Grafo<T1>::Get_aristas()
{
  int cont = 0;
  for(auto it : this->nodos)
  {
    for(auto cc : it->aristas)
    {
      cont++;
    }
  }
  return cont;
}

template<typename T1>
bool menor(Arista<T1>* a, Arista<T1>* b)
{
	return a->peso < b->peso;
}

template <typename T1>
void Grafo<T1>::Insertar_Nodo(T1 data)
{
    auto temp = new Nodo<T1>(data);
    this->nodos.push_back(temp);
}

int Buscar_Padre(int id_nodo, map<int, int> padres)
{
	if (padres[id_nodo] == id_nodo)
	{
		return id_nodo;
	}
	return Buscar_Padre(padres[id_nodo], padres);
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
Grafo<T1>* Grafo<T1>::Invertir_Aristas() {
    Grafo<T1>* graph = new Grafo_dirigido<T1>();
    for(auto nodo : this->nodos)
        graph->Insertar_Nodo(nodo->data);
    graph->Generar_Aristas_Invertidas();
    return graph;
}

template<typename T1>
void Grafo<T1>::DFS(Nodo<T1>*& v, unordered_set<int>& visited) {
    visited.insert(v->data->id);
    for(auto arista : v->aristas) {
        if(!visited.count(arista->nodos[1]->data->id)) {
            v = arista->nodos[1];
            DFS(v, visited);
        }
    }
}

template<typename T1>
bool Grafo<T1>::Es_Conexo() {
    Nodo<T1>* actual = this->nodos[0];
    unordered_set<int> vis1,vis2;
    this->DFS(actual,vis1);
    auto invertido = this->Invertir_Aristas();
    actual = invertido->Buscar_Nodo(actual->data->id);
    invertido->DFS(actual, vis2);
    for(auto nodo : this->nodos) {
        if(!vis1.count(nodo->data->id) && !vis2.count(nodo->data->id))
            return false;
    }
    return true;
}

template<typename T1>
bool Grafo<T1>::Es_Fuertemente_Conexo() {
    Nodo<T1>* inicio = this->nodos[0];
    unordered_set<int>vis1,vis2;
    this->DFS(inicio,vis1);
    if(this->nodos.size() != vis1.size())
        return false;
    auto invertido = this->Invertir_Aristas();
    inicio = invertido->Buscar_Nodo(this->nodos[0]->data->id);
    invertido->DFS(inicio, vis2);
    if(invertido->nodos.size() != vis2.size())
        return false;
    return true;
}

template<typename T1>
bool is_in_vector(vector<Nodo<T1>*>* vectorcito, Nodo<T1>* nodito) {
	for (auto it : *vectorcito) {
		if (it->data->id == nodito->data->id) {
			return true;
		}
	}
	return false;
}

template<typename T1>
Grafo<T1>* Grafo_no_dirigido<T1>::Prim()
{	vector<Arista<T1>*>* vectorcito = new vector<Arista<T1>*>;
	vector<Nodo<T1>*>* vectorcito_nodos = new vector<Nodo<T1>*>;

	auto nodo_temp = this->nodos.front();
	vectorcito_nodos->push_back(nodo_temp);
	auto arista_temp = this->menor_Arista(vectorcito_nodos);
	vectorcito->push_back(arista_temp);
	vectorcito_nodos->clear();
	vectorcito_nodos->push_back(arista_temp->nodos[0]);
	vectorcito_nodos->push_back(arista_temp->nodos[1]);

	int contador = 1;

	while (vectorcito->size() != (this->nodos.size() - 1)) {
		arista_temp = this->menor_Arista(vectorcito_nodos);
		vectorcito->push_back(arista_temp);
		contador++;

		if (!is_in_vector(vectorcito_nodos, arista_temp->nodos[0])) {
			vectorcito_nodos->push_back(arista_temp->nodos[0]);
		}
		else if (!is_in_vector(vectorcito_nodos, arista_temp->nodos[1])) {
			vectorcito_nodos->push_back(arista_temp->nodos[1]);
		}
	}

  Grafo<T1>* MST_graph = new Grafo_no_dirigido<T1>();
  for (auto cc : *vectorcito)
  {
    cc->nodos[0]->aristas.clear();
    cc->nodos[1]->aristas.clear();
  }
  for (auto it : *vectorcito)
  {
    if (MST_graph->Buscar_Nodo(it->nodos[0]->data->id) == nullptr)
    {
      MST_graph->nodos.push_back(it->nodos[0]);
    }
    if (MST_graph->Buscar_Nodo(it->nodos[1]->data->id) == nullptr)
    {
      MST_graph->nodos.push_back(it->nodos[1]);
    }
    it->nodos[0]->aristas.push_back(it);
    it->nodos[1]->aristas.push_back(it);
  }

  return MST_graph;
}

template<typename T1>
Grafo<T1>* Grafo_no_dirigido<T1>::MST_Kruskal()
{
	vector<Arista<T1>*> Krusk = {};
	vector<Arista<T1>*> Aristas_Ordenadas;
	map<int, int> padres;
	for (auto node : this->nodos)
	{
		padres[node->data->id] = node->data->id;
		for (auto ar : node->aristas)
		{
			Aristas_Ordenadas.push_back(ar);
		}
	}

	sort(Aristas_Ordenadas.begin(), Aristas_Ordenadas.end(), menor<T1>);
	int i = 0;
	while (Krusk.size() < this->nodos.size() - 1)
	{
		Arista<T1>* actual = Aristas_Ordenadas[i];
		int padre_inicio = Buscar_Padre(actual->nodos[0]->data->id, padres);
		int padre_final = Buscar_Padre(actual->nodos[1]->data->id, padres);
		if (padre_inicio != padre_final)
		{
			Krusk.push_back(actual);
			padres[padre_inicio] = padre_final;
		}
		i++;
	}
	Grafo<T1>* MST_graph = new Grafo_no_dirigido<T1>();
	for (auto cc : Krusk)
	{
		cc->nodos[0]->aristas.clear();
		cc->nodos[1]->aristas.clear();
	}
	for (auto it : Krusk)
	{
		if (MST_graph->Buscar_Nodo(it->nodos[0]->data->id) == nullptr)
		{
			MST_graph->nodos.push_back(it->nodos[0]);
		}
		if (MST_graph->Buscar_Nodo(it->nodos[1]->data->id) == nullptr)
		{
			MST_graph->nodos.push_back(it->nodos[1]);
		}
		it->nodos[0]->aristas.push_back(it);
		it->nodos[1]->aristas.push_back(it);
	}

	return MST_graph;
}

template<typename T1>
Arista<T1>* Grafo<T1>::menor_Arista(vector<Nodo<T1>*>* vectorcito)
{
	float menor = 1000000.0;

	auto menor_arista = vectorcito->front()->aristas.front();
	for (auto it : *vectorcito) {
		for (auto thi : it->aristas) {
			if (thi->peso < menor) {
				if (!(is_in_vector(vectorcito, thi->nodos[0]) && is_in_vector(vectorcito, thi->nodos[1]))) {
					menor_arista = thi;
					menor = menor_arista->peso;
				}
			}
		}
	}
	return menor_arista;
}

template<typename T1>
void Grafo_dirigido<T1>::Insertar_Arista(int inicio, int fin, float peso) {
  auto it = this->Buscar_Nodo(inicio);
	auto destino = this->Buscar_Nodo(dest);
	auto aux = new Arista<T1>(it, destino);
	it->aristas.push_back(aux);
}

template<typename T1>
Graph<T1>* Graph<T1>::construirGrafo(int inicio, int fin, unordered_map<int, pair<int, float> > padres) {
  if(parents.find(fin) == parents.end()) return nullptr;
  Graph<T1>* res = new Grafo_dirigido<T1>();
  res->Insertar_Nodo(Buscar_Nodo(fin)->getData());
  do {
    res->Insertar_Nodo(Buscar_Nodo(padres[fin].first));
    res->Insertar_Arista(padres[fin].first, fin, padres[fin].second);
    fin = padres[fin].first;
  } while(padres[fin]->first != end);
  return res;
}

template<typename T1>
unordered_map<int, Graph<T1>* > Graph<T1>::BellmanFord(int inicio) {
    unordered_map<int, float> dist;
    unordered_map<Node<T1>*, int> nodos_invertidos;
    float inf = numeric_limits<float>::max();
    vector<Arista<T1>*> aristas;
    unordered_map<int, pair<int, float> > padres;
    padres[inicio] = make_pair(inicio, 0);

    for(auto n : this->nodos) {
        dist[n->data->id] = inf;
        nodos_invertidos[n] = n->data->id;
        vector<Arista<T1>*> aristasDelNodo = n->getEdges();
        for(Arista<T1>* ar : aristasDelNodo)
            aristas.push_back(ar);
    }
    dist[inicio] = 0;

    int V = this->nodos.size();

    for(int i = 0; i < V-1; ++i) {
        for(Arista<T1>* ar : aristas) {
            int u = nodos_invertidos[ar->nodos[0]];
            int v = nodos_invertidos[ar->nodos[1]];
            float weight = ar->getWeight();
            if(dist[u] != inf && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                padres[v] = make_pair(u, peso);
            }
        }
    }

    for(Arista<T1>* ar: aristas) {
        int u = nodos_invertidos[ar->nodos[0]];
        int v = nodos_invertidos[ar->nodos[1]];
        float peso = ar->getWeight();
        if(dist[u] != inf && dist[u] + peso < dist[v])
            cout << "El grafo contiene un ciclo de pesos negativos" << endl;
    }

    unordered_map<N, Graph<T1>*> res;
    for(auto n : this->nodos)
        res[n->data->id] = construirGrafo(inicio, n->data->id, padres);
    return res;
}
template<typename T1>
pair<map<Nodo<T1>*,map<Nodo<T1>*,float> >,map<Nodo<T1>*,map<Nodo<T1>*,Nodo<T1>*> > > Grafo<T1>::FloydWarshall() {
  map<Nodo<T1>*,map<Nodo<T1>*,float> > dist;
  map<Nodo<T1>*,map<Nodo<T1>*,Nodo<T1>*> interm;
  float inf = numeric_limits<float>::max();

  for(auto n1 : this->nodos) {
    for(auto n2 : this->nodos) {
      dist[n1][n2] = n1 == n2 ? 0 : inf;
      interm[n1][n2] = n2;
    }
  }

  for(auto n : this->nodos) {
    for(auto e : n->aristas) {
      Nodo<T1>* n2= e->nodos[1];
      dist[n][n2] = e->getWeight();
      interm[n][n2] = n2;
    }
  }

  for(auto k : this->nodos) {
    for(auto i : this->nodos) {
      for(auto j : this->nodos) {
        if(dist[i][k] < inf && dist[i][j] < inf && dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          interm[i][j] = k;
        }
      }
    }
  }

  return make_pair(dist,interm);
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
