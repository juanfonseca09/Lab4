#ifndef VEHICULO_H
#define VEHICULO_H

#include "TipoVehiculo.h"
#include "DTFecha.h"

#include <string>
#include <vector>

class Conductor;
class Viaje;

class Vehiculo {
private:
    std::string matricula;
    int capacidad;
    std::string marca;
    std::string modelo;
    TipoVehiculo tipo;

    Conductor* conductor;
    std::vector<Viaje*> viajes;

public:
    Vehiculo(std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo);
    ~Vehiculo();

    std::string getMatricula();
    int getCapacidad();
    std::string getMarca();
    std::string getModelo();
    TipoVehiculo getTipo();

    void setConductor(Conductor* conductor);
    Conductor* getConductor();

    void agregarViaje(Viaje* viaje);
    void eliminarViaje(int codigo);
    std::vector<Viaje*> getViajes();

    bool hayViajeFecha(DTFecha fecha);
};

#endif