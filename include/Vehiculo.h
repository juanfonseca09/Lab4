#ifndef VEHICULO_H
#define VEHICULO_H

#include "TipoVehiculo.h"
#include "DTFecha.h"

#include <string>
#include <vector>

class Viaje;
class Conductor;

class Vehiculo {
private:
    std::string matricula;
    int capacidad;
    std::string marca;
    std::string modelo;
    TipoVehiculo tipo;
    std::vector<Viaje*> viajes;
    Conductor* conductor;
public:
    Vehiculo(std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo, Conductor* conductor);
    virtual ~Vehiculo();
    std::string getMatricula() const;
    Conductor* getConductor() const;
    int getCapacidad() const;
    std::string getMarca() const;
    std::string getModelo() const;
    TipoVehiculo getTipo() const;
    void agregarViaje(Viaje* viaje);
    std::vector<Viaje*> getViajes() const;
    bool hayViajeFecha(DTFecha fecha) const;
    void eliminarViaje(int codigo);
};

#endif