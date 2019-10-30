#include <iostream>
#include <json/value.h>
#include <json/json.h>
#include <fstream>
#include "Grafo.h"


int main()
{
	Json::Value aeropuertos;
	ifstream aeropuertos_file("airports.json", ios::in);
	aeropuertos_file >> aeropuertos;
	
	//std::cout << aeropuertos;
	Grafo<Aeropuerto*> graph;
	vector<int> destinos;

	for (int i = 0; i < aeropuertos.size(); i++) {
		for (int k = 0; k < aeropuertos[i]["destinations"].size(); k++) {
			destinos.push_back(stoi(aeropuertos[i]["destinations"][k].asString()));
		}
		if(isdigit(aeropuertos[i]["Latitude"].asString()[0]))
			graph.Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), stof(aeropuertos[i]["Latitude"].asString()), stoi(aeropuertos[i]["Id"].asString()), destinos));
		else {
			graph.Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), 0, stoi(aeropuertos[i]["Id"].asString()), destinos));

		}
		
		destinos.clear();
	}

	graph.Generar_Aristas_noDirec();

	//graph.Imprimir_Grafo();

	cout << graph.nodos.size();
	auto min_prim = graph.Prim();

	cout << "\n\n\n\n";

	for (auto it : min_prim) {
		cout << it->nodos[0]->data->Nombre<<"  "<< it->nodos[1]->data->Nombre << endl;
	}

	return EXIT_SUCCESS;

}

