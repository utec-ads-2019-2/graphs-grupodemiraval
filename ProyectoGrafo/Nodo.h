//
// Created by PROPIETARIO on 23/10/2019.
//

#ifndef PROYECTOGRAFO_NODO_H
#define PROYECTOGRAFO_NODO_H
#include "Arista.h"
#include <vector>
#include <iostream>

using namespace std;

template <typename T1>
class Nodo {
public:
    T1 data;
    float posx, posy;
    vector<Arista<T1>*> aristas;
    Nodo(T1 data):data{data},posx{0},posy{0}
    {
        posx = data->Longitud;
        posy = data->Latitud;
    }
    void Imprimir_Aristas();
};
template <typename T1>
void Nodo<T1>::Imprimir_Aristas()
{
    cout<<"Aristas del nodo: "<<this->data->id<<endl;
    for(auto it : this->aristas)
    {
        cout<<"Origen: "<<it->nodos[0]->data->id<<" / "<<"Final: "<<it->nodos[1]->data->id<<endl;
    }
}

#endif //PROYECTOGRAFO_NODO_H
