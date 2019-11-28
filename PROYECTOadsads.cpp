#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "Grafo.h"


int main()
{

	Json::Value aeropuertos;
	ifstream aeropuertos_file("airports.json", ios::in);
	aeropuertos_file >> aeropuertos;
	Grafo<Aeropuerto*>* graph = new Grafo_dirigido<Aeropuerto*>;
	vector<int> destinos;


	for (int i = 0; i < aeropuertos.size(); i++) {
		for (int k = 0; k < aeropuertos[i]["destinations"].size(); k++) {
			destinos.push_back(stoi(aeropuertos[i]["destinations"][k].asString()));
		}
		if(isdigit(aeropuertos[i]["Latitude"].asString()[0]))
			graph->Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), stof(aeropuertos[i]["Latitude"].asString()), stoi(aeropuertos[i]["Id"].asString()), destinos));
		else {
			graph->Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), 0, stoi(aeropuertos[i]["Id"].asString()), destinos));

		}

		destinos.clear();
	}
	graph->Generar_Aristas();
//	graph->Imprimir_Grafo();
	cout <<"El grafo tiene: "<<graph->nodos.size()<<" nodos"<<endl;

	auto vec1 = graph->Busqueda_A(7188,4025);
	// for(auto it : ve1c)
	// {
	// 	cout<<it->nodos[0]->data->id<<" "<<it->nodos[1]->data->id<<endl;
	// }

	cout<<endl<<"Ejecutando algoritmo Dijkstra"<<endl;
	auto vec2 = graph->Dijkstra(7188);
	cout<<endl;
	for(auto it : vec2)
	{
		cout<<it->nodos[0]->data->id<<" "<<it->nodos[1]->data->id<<endl;
	}

	cout<<endl<<"Ejecutando algoritmo BellmanFord"<<endl;
	auto vec3 = graph->BellmanFord(7188);
	for(auto i : vec3) {
		cout << "cammmmmino a  " << i.first << endl;
		i.second->Imprimir_Grafo();
	}

	cout<<endl<<"Ejecutando FloydWarshall"<<endl;

	auto vec4 = graph->FloydWarshall();
for(auto a : vec4.first) {
	cout << "Nodooooooooooo: "<< a.first->data->id << endl;
	for(auto b : a.second) {
		cout <<  "dest: " << b.first->data->id				 << " peso " << b.second << endl;
	}
}


	return EXIT_SUCCESS;

}
