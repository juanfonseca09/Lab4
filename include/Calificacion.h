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
    DTFecha getFecha() const;
    int getPuntaje() const;
    Usuario* getEvaluador() const;
    Usuario* getEvaluado() const;
    Reserva* getReserva() const;
    bool esDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) const;
    // se usa para saber si una persona ya califico a otra
};

#endif