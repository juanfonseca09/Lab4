#ifndef VIAJE_H
#define VIAJE_H

#include "DTFecha.h"
#include "Vehiculo.h"
#include "Reserva.h"
#include "DTDetalleViaje.h"

#include <string>
#include <vector>

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
    Viaje(int codigo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio);
    Viaje(int codigo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio, Vehiculo* vehiculo);
    ~Viaje();

    int getCodigo() const;
    DTFecha getFecha() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    int getAsientosPublicados() const;
    float getPrecio() const;
    Vehiculo* getVehiculo() const;

    int getAsientosReservados() const;
    int getAsientosDisponibles() const;
    bool tieneDisponibilidad(int cantidadAsientos) const;

    void agregarReserva(Reserva* reserva);
    std::vector<Reserva*> getReservas() const;

    bool tieneReservaDePasajero(std::string nicknamePasajero) const;
    Reserva* buscarReservaDePasajero(std::string nicknamePasajero) const;

    bool coincideCon(DTFecha fecha, std::string origen, std::string destino, int cantidadAsientos) const;

    DTDetalleViaje getDetalle() const;
};

#endif