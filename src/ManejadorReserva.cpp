#include "../include/ManejadorReserva.h"

ManejadorReserva* ManejadorReserva::instancia = 0;

ManejadorReserva::ManejadorReserva() {
}

ManejadorReserva* ManejadorReserva::getInstance() {
    if (instancia == 0)
        instancia = new ManejadorReserva();
    return instancia;
}

void ManejadorReserva::agregarReserva(Reserva* r) {
    if (r != 0)
        reservas.push_back(r);
}

std::vector<Reserva*> ManejadorReserva::getReservas() {
    return reservas;
}