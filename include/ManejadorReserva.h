#ifndef MANEJADOR_RESERVA_H
#define MANEJADOR_RESERVA_H

#include <vector>

class Reserva;

class ManejadorReserva {
private:
    static ManejadorReserva* instancia;
    std::vector<Reserva*> reservas;
    ManejadorReserva();
public:
    ~ManejadorReserva();
    static ManejadorReserva* getInstance();
    void agregarReserva(Reserva* r);
    std::vector<Reserva*> getReservas();
};

#endif