#include <iostream>
#include <json/value.h>
#include <json/json.h>
#include <fstream>
#include "Grafo.h"

using namespace std;

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


int main()
{
	Json::Value aeropuertos;
	ifstream aeropuertos_file("airports.json", ios::in);
	aeropuertos_file >> aeropuertos;
	Grafo<Aeropuerto*>* graph;
	vector<int> destinos;
	string es;

	cout << "El grafo es dirigido (D) o no dirigido (ND)?" << endl;

	cin >> es;
	if (es == "D") {
		graph = new Grafo_dirigido<Aeropuerto*>;
	}
	else{
		graph = new Grafo_no_dirigido<Aeropuerto*>;
	}



	for (unsigned int i = 0; i < aeropuertos.size(); i++) {
		for (unsigned int k = 0; k < aeropuertos[i]["destinations"].size(); k++) {
			destinos.push_back(stoi(aeropuertos[i]["destinations"][k].asString()));
		}
		if (isdigit(aeropuertos[i]["Latitude"].asString()[0]))
			graph->Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), stof(aeropuertos[i]["Latitude"].asString()), stoi(aeropuertos[i]["Id"].asString()), destinos));
		else {
			graph->Insertar_Nodo(new Aeropuerto(aeropuertos[i]["City"].asString(), aeropuertos[i]["Name"].asString(), aeropuertos[i]["Country"].asString(), stof(aeropuertos[i]["Longitude"].asString()), 0, stoi(aeropuertos[i]["Id"].asString()), destinos));

		}

		destinos.clear();
	}
	graph->Generar_Aristas();
	//	graph->Imprimir_Grafo();

	cout << "El grafo tiene: " << graph->nodos.size() << " nodos" << endl;

	cout << (graph->Es_Bipartito() ? "es bipartito" : "no es bipartito") << endl;

	cout << (graph->Es_Conexo() ? "es conexo" : "no es conexo") << endl;

	cout << (graph->Es_Fuertemente_Conexo() ? "es fuertemente conexo" : "no es fuertemente conexo") << endl;

	double cota = 0.6;
	graph->Densidad(cota);

	graph->Ejecutar();

	graph->Dijktra(7252);

	// if (es == "ND") {
	// 	cout << "Ejecutando el MST : PRIM : " << endl;
	//
	// 	auto min_prim = graph->Prim();
	// 	int counter = 1;
	// 	cout << "\n\n\n";
	//
	// 	for (auto it : min_prim) {
	// 		cout << "Arista " << counter << ":" << endl;
	// 		cout << "Nombre de salida:" << it->nodos[0]->data->id << "  " << "Nombre de entrada: " << it->nodos[1]->data->id << endl;
	// 		cout << "Id de salida:" << it->nodos[0]->data->id << "  " << "Id de entrada: " << it->nodos[1]->data->id << endl;
	// 		cout << "\n\n";
	// 		counter++;
	// 	}
	// 	cout << "Ejecutando el MST : KRUSKAL : " << endl;
	//
	// 	auto a = graph->MST_Kruskal();
	// 	for (auto i : a.nodos)
	// 	{
	// 		i->Imprimir_Aristas();
	// 	}
	//
	//
	// }







	return EXIT_SUCCESS;

}