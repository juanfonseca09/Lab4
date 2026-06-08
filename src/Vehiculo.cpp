#include "../include/Vehiculo.h"

Vehiculo::Vehiculo(std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) {
    this->matricula = matricula;
    this->capacidad = capacidad;
    this->marca = marca;
    this->modelo = modelo;
    this->tipo = tipo;
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