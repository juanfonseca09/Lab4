#include "../include/Pasajero.h"

Pasajero::Pasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci)
    : Usuario(nickname, nombre, contrasena, email) {
    this->ci = ci;
}

Pasajero::~Pasajero() {
}

std::string Pasajero::getCI() const {
    return ci;
}

void Pasajero::agregarReserva(Reserva* reserva) {
    if (reserva != NULL)
        reservas.push_back(reserva);
}

std::vector<Reserva*> Pasajero::getReservas() const {
    return reservas;
}