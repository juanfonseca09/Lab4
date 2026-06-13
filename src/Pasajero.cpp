#include "../include/Pasajero.h"
#include "../include/Reserva.h"
#include "../include/Viaje.h"

Pasajero::Pasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci)
    : Usuario(nickname, nombre, contrasena, email) {
    this->ci = ci;
}

Pasajero::~Pasajero() {
}

std::string Pasajero::getCI() {
    return ci;
}

void Pasajero::agregarReserva(Reserva* reserva) {
    if (reserva != NULL) {
        reservas.push_back(reserva);
    }
}

std::vector<Reserva*> Pasajero::getReservas() {
    return reservas;
}

void Pasajero::eliminarReferenciaReservaDeViaje(Viaje* viaje) {
    std::vector<Reserva*> nuevasReservas;

    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i] != NULL && reservas[i]->getViaje() == viaje) {
            continue;
        }

        nuevasReservas.push_back(reservas[i]);
    }

    reservas = nuevasReservas;
}