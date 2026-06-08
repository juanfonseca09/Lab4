#include "../include/DTFecha.h"

DTFecha::DTFecha() {
    this->dia = 1;
    this->mes = 1;
    this->anio = 1900;
}

DTFecha::DTFecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

int DTFecha::getDia() const {
    return dia;
}

int DTFecha::getMes() const {
    return mes;
}

int DTFecha::getAnio() const {
    return anio;
}

bool DTFecha::operator==(const DTFecha& other) const {
    return dia == other.dia &&
           mes == other.mes &&
           anio == other.anio;
}

bool DTFecha::operator<(const DTFecha& other) const {
    if (anio != other.anio) {
        return anio < other.anio;
    }

    if (mes != other.mes) {
        return mes < other.mes;
    }

    return dia < other.dia;
}

std::ostream& operator<<(std::ostream& os, const DTFecha& f) {
    os << f.getDia() << "/" << f.getMes() << "/" << f.getAnio();
    return os;
}