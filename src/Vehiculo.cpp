#include "../include/Vehiculo.h"
#include "../include/Viaje.h"

Vehiculo::Vehiculo(std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo, Conductor* c) {
    this->matricula = matricula;
    this->capacidad = capacidad;
    this->marca = marca;
    this->modelo = modelo;
    this->tipo = tipo;
    this->conductor = c;
}

Vehiculo::~Vehiculo() {
}

std::string Vehiculo::getMatricula() const {
    return matricula;
}

int Vehiculo::getCapacidad() const {
    return capacidad;
}

std::string Vehiculo::getMarca() const {
    return marca;
}

std::string Vehiculo::getModelo() const {
    return modelo;
}

TipoVehiculo Vehiculo::getTipo() const {
    return tipo;
}

Conductor* Vehiculo::getConductor() const {
    return conductor;
}

void Vehiculo::agregarViaje(Viaje* viaje) {
    if (viaje != NULL)
        viajes.push_back(viaje);
}

std::vector<Viaje*> Vehiculo::getViajes() const {
    return viajes;
}

bool Vehiculo::hayViajeFecha(DTFecha fecha) const {
    for (unsigned  i = 0; i < viajes.size(); i++) {
        if (viajes[i]->getFecha() == fecha)
            return true;
    }
    return false;
}

void Vehiculo::eliminarViaje(int codigo) {
    for (unsigned  i = 0; i < viajes.size(); i++) {
        if (viajes[i]->getCodigo() == codigo) {
            viajes.erase(viajes.begin() + i);
            return;
        }
    }
}