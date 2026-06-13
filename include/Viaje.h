#ifndef VIAJE_H
#define VIAJE_H

#include "DTFecha.h"
#include "DTDetalleViaje.h"

#include <string>
#include <vector>

class Vehiculo;
class Reserva;

class Viaje {
private:
    int codigo;
    DTFecha fecha;
    std::string origen;
    std::string destino;
    int asientosPublicados;
    float precio;

    Vehiculo* vehiculo;
    std::vector<Reserva*> reservas;

public:
    Viaje(int codigo, Vehiculo* vehiculo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio);
    ~Viaje();

    int getCodigo();
    DTFecha getFecha();
    std::string getOrigen();
    std::string getDestino();
    int getAsientosPublicados();
    float getPrecio();

    Vehiculo* getVehiculo();

    void agregarReserva(Reserva* reserva);
    std::vector<Reserva*> getReservas();

    int getAsientosReservados();
    int getAsientosDisponibles();
    bool tieneDisponibilidad(int cantidadAsientos);

    bool tieneReservaDePasajero(std::string nicknamePasajero);
    Reserva* buscarReservaDePasajero(std::string nicknamePasajero);

    bool coincideCon(DTFecha fecha, std::string origen, std::string destino, int cantidadAsientos);

    DTDetalleViaje getDetalle();
};

#endif