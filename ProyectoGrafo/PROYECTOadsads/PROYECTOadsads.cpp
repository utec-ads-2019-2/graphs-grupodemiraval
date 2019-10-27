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
	/*

	Grafo<Aeropuerto*> graph;
	vector<int> destinos1 = {2,4};
	vector<int> destinos2 = {1,3};
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.0, 1.0, 1, destinos1));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.1, 1.0, 2, destinos2));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.2, 1.0, 3, destinos1));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.3, 1.0, 4, destinos2));
	vector<int> destinos3 = {6,7};
	vector<int> destinos4 = {5};
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.4, 1.0, 5, destinos3));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.5, 1.0, 6, destinos4));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 1.6, 1.0, 7, destinos4));
	*/
	graph.Generar_Aristas();

	graph.Imprimir_Grafo();

	cout << (graph.Es_Bipartito() ? "es bipartito" : "no es bipartito") << endl;

	cout << graph.nodos.size();

	return EXIT_SUCCESS;

}

