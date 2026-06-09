#ifndef PASAJERO_H
#define PASAJERO_H

#include "Usuario.h"
#include <string>

class Reserva;

class Pasajero : public Usuario {
private:
    std::string ci;
    std::vector<Reserva*> reservas;
public:
    Pasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci);
    virtual ~Pasajero();
    std::string getCI() const;
    void agregarReserva(Reserva* reserva);
    std::vector<Reserva*> getReservas() const;
};

#endif