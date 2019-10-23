//
// Created by PROPIETARIO on 23/10/2019.
//

#ifndef PROYECTOGRAFO_NODO_H
#define PROYECTOGRAFO_NODO_H
#include "Arista.h"
#include <vector>

template <typename T1>
class Nodo {
    T1 data;
    double posx, posy;
    std::vector<Arista*> aristas;
public:
    Nodo(T1 data):data{data},posx{0},posy{0}{}
};


#endif //PROYECTOGRAFO_NODO_H
