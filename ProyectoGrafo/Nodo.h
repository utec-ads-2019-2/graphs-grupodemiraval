//
// Created by PROPIETARIO on 23/10/2019.
//

#ifndef PROYECTOGRAFO_NODO_H
#define PROYECTOGRAFO_NODO_H
#include "Arista.h"
#include <vector>

template <typename T1>
class Nodo {
public:
    T1 data;
    float posx, posy;
    std::vector<Arista<T1>*> aristas;
    Nodo(T1 data):data{data},posx{0},posy{0}
    {
        posx = data->Longitud;
        posy = data->Latitud;
    }
};


#endif //PROYECTOGRAFO_NODO_H
