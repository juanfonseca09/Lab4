#ifndef RESERVA_H
#define RESERVA_H

#include "DTFecha.h"
#include "DTDetalleReserva.h"

#include <vector>
#include <string>

class Pasajero;
class Calificacion;
class Viaje;

class Reserva {
private:
    int asientosReservados;
    DTFecha fecha;
    Pasajero* pasajero;
    Viaje* viaje;
    std::vector<Calificacion*> calificaciones;
public:
    Reserva(int asientosReservados, DTFecha fecha, Pasajero* pasajero, Viaje* viaje);
    virtual ~Reserva();
    int getAsientosReservados() const;
    DTFecha getFecha() const;
    Pasajero* getPasajero() const;
    Viaje* getViaje() const;
    bool perteneceAPasajero(std::string nickname) const;
    void agregarCalificacion(Calificacion* calificacion);
    std::vector<Calificacion*> getCalificaciones() const;
    bool tieneCalificacionDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) const;
    DTDetalleReserva getDetalle() const;
};

#endif