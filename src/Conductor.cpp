#include "../include/Conductor.h"

Conductor::Conductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libs)
    : Usuario(nickname, nombre, contrasena, email) {
    this->libretas = libs;
}

Conductor::~Conductor() {
    for (unsigned int i = 0; i < vehiculos.size(); i++) {
        delete vehiculos[i];
    }
}

std::set<TipoLibreta> Conductor::getLibretas() {
    return libretas;
}

bool Conductor::tieneLibreta(TipoLibreta libreta) {
    return libretas.find(libreta) != libretas.end();
}

bool Conductor::puedeConducir(TipoVehiculo tipoVehiculo) {
    if (tipoVehiculo == Auto) {
        return tieneLibreta(AutoAmateur) || tieneLibreta(AutoProfesional);
    }

    if (tipoVehiculo == Moto) {
        return tieneLibreta(MotoAmateur) || tieneLibreta(MotoProfesional);
    }

    return false;
}

bool Conductor::agregarVehiculo(Vehiculo* vehiculo) {
    if (vehiculo == NULL) {
        return false;
    }

    if (tieneVehiculo(vehiculo->getMatricula())) {
        return false;
    }

    if (!puedeConducir(vehiculo->getTipo())) {
        return false;
    }

    vehiculo->setConductor(this);
    vehiculos.push_back(vehiculo);

    return true;
}

Vehiculo* Conductor::buscarVehiculo(std::string matricula) {
    for (unsigned int i = 0; i < vehiculos.size(); i++) {
        if (vehiculos[i]->getMatricula() == matricula) {
            return vehiculos[i];
        }
    }

    return NULL;
}

bool Conductor::tieneVehiculo(std::string matricula) {
    return buscarVehiculo(matricula) != NULL;
}

std::vector<Vehiculo*> Conductor::getVehiculos() {
    return vehiculos;
}