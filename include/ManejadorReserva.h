#ifndef MANEJADOR_RESERVA_H
#define MANEJADOR_RESERVA_H

#include "Reserva.h"

#include <vector>

class Viaje;

class ManejadorReserva {
private:
    static ManejadorReserva* instancia;

    std::vector<Reserva*> reservas;

    ManejadorReserva();

public:
    static ManejadorReserva* getInstance();

    void agregarReserva(Reserva* reserva);

    std::vector<Reserva*> getReservas();

    void eliminarReferenciasReservasDeViaje(Viaje* viaje);
};

#endif