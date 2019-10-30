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
	vector<int> destinos1 = {10,2,5};
	vector<int> destinos2 = {1,6,9,3};
	vector<int> destinos3 = {4,2,10};
	vector<int> destinos4 = {3,8,10,5};
	vector<int> destinos5 = {1,4,6,7};
	vector<int> destinos6 = {5,2,10};
	vector<int> destinos7 = {5,9,8};
	vector<int> destinos8 = {4,7,9};
	vector<int> destinos9 = {2,7,8};
	vector<int> destinos10 = {1,6,3,4};
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 100, 1, destinos1));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 200, 2, destinos2));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 300, 3, destinos3));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 400, 4, destinos4));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 500, 5, destinos5));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 600, 6, destinos6));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 700, 7, destinos7));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 800, 8, destinos8));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 900, 9, destinos9));
	graph.Insertar_Nodo(new Aeropuerto("City", "Name", "Country", 100, 1000, 10, destinos10));*/


	graph.Generar_Aristas_noDirec();
	auto a = graph.MST_Kruskal();
	for(auto i : a.nodos)
	{
		i->Imprimir_Aristas();
	}


	return EXIT_SUCCESS;

}
