#include "../include/ManejadorReserva.h"
#include "../include/Reserva.h"

ManejadorReserva* ManejadorReserva::instancia = 0;

ManejadorReserva::ManejadorReserva() {
}

ManejadorReserva::~ManejadorReserva() {
    while (!reservas.empty())
    {
        Reserva* a_borrar = reservas.back();
        reservas.pop_back();
        delete a_borrar;
    }
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