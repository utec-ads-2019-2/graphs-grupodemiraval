#include <iostream>
#include "Grafo.h"
#include "Aeropuerto.h"

using namespace std;

int main() {
    Grafo<Aeropuerto*> graph;
    vector<int> destinos1 = {222,444};
    vector<int> destinos2 = {111,444};
    vector<int> destinos3 = {222,111};
    vector<int> destinos4 = {333};
    graph.Insertar_Nodo( new Aeropuerto("Lima","Jorge Chavez","Peru",100,200,111,destinos1));
    graph.Insertar_Nodo(new Aeropuerto("Cali","Col2","Colombia",100,500,222,destinos2));
    graph.Insertar_Nodo(new Aeropuerto("Buenos Aires","Bombo","Argentina",200,50.5,333,destinos3));
    graph.Insertar_Nodo(new Aeropuerto("Quito","Atahualpa","Ecuador",121,600,444,destinos4));
    graph.Generar_Aristas();
    graph.Imprimir_Grafo();
    cout<<graph.Buscar_Arista(111,444)->peso<<endl;
    graph.Remover_Arista(111,444);
    graph.Remover_Nodo(111);
    graph.Imprimir_Grafo();

}