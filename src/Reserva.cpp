#include "../include/Reserva.h"
#include "../include/Pasajero.h"
#include "../include/Calificacion.h"

Reserva::Reserva(int asientosReservados, DTFecha fecha, Pasajero* pasajero, Viaje* viaje) {
    this->asientosReservados = asientosReservados;
    this->fecha = fecha;
    this->pasajero = pasajero;
    this->viaje = viaje;
}

Reserva::~Reserva() {
    for (unsigned int i = 0; i < calificaciones.size(); i++) {
        delete calificaciones[i];
    }
}

int Reserva::getAsientosReservados() {
    return asientosReservados;
}

DTFecha Reserva::getFecha() {
    return fecha;
}

Pasajero* Reserva::getPasajero() {
    return pasajero;
}

Viaje* Reserva::getViaje() {
    return viaje;
}

bool Reserva::perteneceAPasajero(std::string nickname) {
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

std::vector<Calificacion*> Reserva::getCalificaciones() {
    return calificaciones;
}

bool Reserva::tieneCalificacionDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) {
    for (unsigned int i = 0; i < calificaciones.size(); i++) {
        if (calificaciones[i]->esDePara(nicknameEvaluador, nicknameEvaluado)) {
            return true;
        }
    }

    return false;
}

DTDetalleReserva Reserva::getDetalle() {
    std::string nicknamePasajero = "";

    if (pasajero != NULL) {
        nicknamePasajero = pasajero->getNickname();
    }

    return DTDetalleReserva(asientosReservados, fecha, nicknamePasajero);
}