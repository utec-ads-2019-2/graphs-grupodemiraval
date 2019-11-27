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
	string es;

/*	cout << "El grafo es dirigido (D) o no dirigido (ND)?" << endl;

		cin >> es;
		if (es == "D") {
			graph = new Grafo_dirigido<Aeropuerto*>;
		}
		else if (es == "ND") {
			graph = new Grafo_no_dirigido<Aeropuerto*>;
		}
*/


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

	graph->Busqueda_A(7188,4025);
	graph->BellmanFord(1285);

/*	cout << (graph->Es_Bipartito() ? "es bipartito" : "no es bipartito") << endl;

	cout << (graph->Es_Conexo() ? "es conexo" : "no es conexo") << endl;

	cout << (graph->Es_Fuertemente_Conexo() ? "es fuertemente conexo" : "no es fuertemente conexo") << endl;

	double cota = 0.6;
	graph->Densidad(cota);

	graph->Ejecutar();

*/



	return EXIT_SUCCESS;

}
