#ifndef CALIFICACION_H
#define CALIFICACION_H

#include "DTFecha.h"

#include <string>

class Usuario;
class Reserva;

class Calificacion {
private:
    DTFecha fecha;
    int puntaje;

    Usuario* evaluador;
    Usuario* evaluado;
    Reserva* reserva;

public:
    Calificacion(DTFecha fecha, int puntaje, Usuario* evaluador, Usuario* evaluado, Reserva* reserva);
    ~Calificacion();

    DTFecha getFecha();
    int getPuntaje();

    Usuario* getEvaluador();
    Usuario* getEvaluado();
    Reserva* getReserva();

    bool esDePara(std::string nicknameEvaluador, std::string nicknameEvaluado);
};

#endif