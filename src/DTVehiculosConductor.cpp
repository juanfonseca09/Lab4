#include "../include/DTVehiculosConductor.h"

DTVehiculosConductor::DTVehiculosConductor() {
    this->matricula = "";
    this->marca = "";
    this->capacidad = 0;
}

DTVehiculosConductor::DTVehiculosConductor(std::string matricula, std::string marca, int capacidad) {
    this->matricula = matricula;
    this->marca = marca;
    this->capacidad = capacidad;
}

std::string DTVehiculosConductor::getMatricula() const {
    return matricula;
}

std::string DTVehiculosConductor::getMarca() const {
    return marca;
}

int DTVehiculosConductor::getCapacidad() const {
    return capacidad;
}