#ifndef PASAJERO_H
#define PASAJERO_H

#include "Usuario.h"

#include <string>
#include <vector>

class Reserva;
class Viaje;

class Pasajero : public Usuario {
private:
    std::string ci;
    std::vector<Reserva*> reservas;

public:
    Pasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci);
    virtual ~Pasajero();

    std::string getCI();

    void agregarReserva(Reserva* reserva);
    std::vector<Reserva*> getReservas();

    void eliminarReferenciaReservaDeViaje(Viaje* viaje);
};

#endif