#include <iostream>
#include <vector>

using namespace std;

class Aeropuerto {
private:
	string Ciudad;
	string Nombre;
	string Pais;
	float Longitud;
	float Latitud;
	int id;
	vector <int> destinos;

public:
	void clear() {
		destinos.clear();
	}
	
	Aeropuerto(string Ciudad, string Nombre, string Pais, float Longitud, float Latitud, int id, vector<int> destinos) :
		Ciudad{ Ciudad }, Nombre{ Nombre }, Pais{ Pais }, Longitud{ Longitud }, Latitud{ Latitud }, id{ id }, destinos{ destinos }{}
	Aeropuerto(Aeropuerto* aeropuerto, bool copiarDestinos = true) : 
		Ciudad{aeropuerto->Ciudad}, Nombre{aeropuerto->Nombre}, Pais{aeropuerto->Pais},
		Longitud{aeropuerto->Longitud}, Latitud{aeropuerto->Latitud}, id{aeropuerto->id}{
			if(copiarDestinos)
				for(int i : aeropuerto->destinos)
					destinos.push_back(i);
		}
	Aeropuerto* AeropuertoSinDestinos(Aeropuerto* aeropuerto) {
		return new Aeropuerto(aeropuerto, false);
	}
};