//
// Created by PROPIETARIO on 23/10/2019.
//

#ifndef PROYECTOGRAFO_AEROPUERTO_H
#define PROYECTOGRAFO_AEROPUERTO_H

#include <iostream>
#include <vector>
using namespace std;

class Aeropuerto {
    string Ciudad;
    string Nombre;
    string Pais;
    float Longitud;
    float Latitud;
    int id;
    vector <string> destinos;
public:
    Aeropuerto(string Ciudad, string Nombre, string Pais, float Longitud, float Latitud, int id, vector<string> destinos):
    Ciudad{Ciudad},Nombre{Nombre},Pais{Pais},Longitud{Longitud},Latitud{Latitud},id{id},destinos{destinos}{}
};


#endif //PROYECTOGRAFO_AEROPUERTO_H
