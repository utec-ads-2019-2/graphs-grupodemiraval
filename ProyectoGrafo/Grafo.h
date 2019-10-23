//
// Created by PROPIETARIO on 23/10/2019.
//

#ifndef PROYECTOGRAFO_GRAFO_H
#define PROYECTOGRAFO_GRAFO_H

#include <vector>
#include "Nodo.h"

using namespace std;
template<typename T1>
class Grafo {
    vector<Nodo<T1>*> nodos;
public:
    Grafo()=default;
    void Insertar_Nodo(T1 data);
};


#endif //PROYECTOGRAFO_GRAFO_H
