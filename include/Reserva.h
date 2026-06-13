#ifndef RESERVA_H
#define RESERVA_H

#include "DTFecha.h"
#include "DTDetalleReserva.h"

#include <vector>
#include <string>

class Pasajero;
class Viaje;
class Calificacion;

class Reserva {
private:
    int asientosReservados;
    DTFecha fecha;

    Pasajero* pasajero;
    Viaje* viaje;

    std::vector<Calificacion*> calificaciones;

public:
    Reserva(int asientosReservados, DTFecha fecha, Pasajero* pasajero, Viaje* viaje);
    ~Reserva();

    int getAsientosReservados();
    DTFecha getFecha();

    Pasajero* getPasajero();
    Viaje* getViaje();

    bool perteneceAPasajero(std::string nickname);

    void agregarCalificacion(Calificacion* calificacion);
    std::vector<Calificacion*> getCalificaciones();

    bool tieneCalificacionDePara(std::string nicknameEvaluador, std::string nicknameEvaluado);

    DTDetalleReserva getDetalle();
};

#endif