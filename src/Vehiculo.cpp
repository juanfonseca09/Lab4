#include "../include/Vehiculo.h"
#include "../include/Viaje.h"

Vehiculo::Vehiculo(std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) {
    this->matricula = matricula;
    this->capacidad = capacidad;
    this->marca = marca;
    this->modelo = modelo;
    this->tipo = tipo;
    this->conductor = NULL;
}

Vehiculo::~Vehiculo() {
}

std::string Vehiculo::getMatricula() {
    return matricula;
}

int Vehiculo::getCapacidad() {
    return capacidad;
}

std::string Vehiculo::getMarca() {
    return marca;
}

std::string Vehiculo::getModelo() {
    return modelo;
}

TipoVehiculo Vehiculo::getTipo() {
    return tipo;
}

void Vehiculo::setConductor(Conductor* conductor) {
    this->conductor = conductor;
}

Conductor* Vehiculo::getConductor() {
    return conductor;
}

void Vehiculo::agregarViaje(Viaje* viaje) {
    if (viaje != NULL) {
        viajes.push_back(viaje);
    }
}

void Vehiculo::eliminarViaje(int codigo) {
    std::vector<Viaje*> nuevosViajes;

    for (unsigned int i = 0; i < viajes.size(); i++) {
        if (viajes[i] != NULL && viajes[i]->getCodigo() == codigo) {
            continue;
        }

        nuevosViajes.push_back(viajes[i]);
    }

    viajes = nuevosViajes;
}

std::vector<Viaje*> Vehiculo::getViajes() {
    return viajes;
}

bool Vehiculo::hayViajeFecha(DTFecha fecha) {
    for (unsigned int i = 0; i < viajes.size(); i++) {
        if (viajes[i] != NULL && viajes[i]->getFecha() == fecha) {
            return true;
        }
    }

    return false;
}