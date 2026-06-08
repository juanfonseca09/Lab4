#include "../include/Reserva.h"
#include "../include/Pasajero.h"
#include "../include/Calificacion.h"

Reserva::Reserva(int asientosReservados, DTFecha fecha) {
    this->asientosReservados = asientosReservados;
    this->fecha = fecha;
    this->pasajero = NULL;
}

Reserva::Reserva(int asientosReservados, DTFecha fecha, Pasajero* pasajero) {
    this->asientosReservados = asientosReservados;
    this->fecha = fecha;
    this->pasajero = pasajero;
}

Reserva::~Reserva() {
    for (unsigned int i = 0; i < calificaciones.size(); i++) {
        delete calificaciones[i];
    }
}

int Reserva::getAsientosReservados() const {
    return asientosReservados;
}

DTFecha Reserva::getFecha() const {
    return fecha;
}

Pasajero* Reserva::getPasajero() const {
    return pasajero;
}

bool Reserva::perteneceAPasajero(std::string nickname) const {
    if (pasajero == NULL) {
        return false;
    }

    return pasajero->getNickname() == nickname;
}

void Reserva::agregarCalificacion(Calificacion* calificacion) {
    if (calificacion != NULL) {
        calificaciones.push_back(calificacion);
    }
}

std::vector<Calificacion*> Reserva::getCalificaciones() const {
    return calificaciones;
}

bool Reserva::tieneCalificacionDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) const {
    for (unsigned int i = 0; i < calificaciones.size(); i++) {
        if (calificaciones[i]->esDePara(nicknameEvaluador, nicknameEvaluado)) {
            return true;
        }
    }

    return false;
}

DTDetalleReserva Reserva::getDetalle() const {
    std::string nicknamePasajero = "";

    if (pasajero != NULL) {
        nicknamePasajero = pasajero->getNickname();
    }

    return DTDetalleReserva(asientosReservados, fecha, nicknamePasajero);
}