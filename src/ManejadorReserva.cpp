#include "../include/ManejadorReserva.h"
#include "../include/Viaje.h"

ManejadorReserva* ManejadorReserva::instancia = NULL;

ManejadorReserva::ManejadorReserva() {
}

ManejadorReserva* ManejadorReserva::getInstance() {
    if (instancia == NULL) {
        instancia = new ManejadorReserva();
    }

    return instancia;
}

void ManejadorReserva::agregarReserva(Reserva* reserva) {
    if (reserva != NULL) {
        reservas.push_back(reserva);
    }
}

std::vector<Reserva*> ManejadorReserva::getReservas() {
    return reservas;
}

void ManejadorReserva::eliminarReferenciasReservasDeViaje(Viaje* viaje) {
    std::vector<Reserva*> nuevasReservas;

    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i] != NULL && reservas[i]->getViaje() == viaje) {
            continue;
        }

        nuevasReservas.push_back(reservas[i]);
    }

    reservas = nuevasReservas;
}