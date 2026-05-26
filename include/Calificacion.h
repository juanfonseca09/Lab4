#ifndef CALIFICACION_H
#define CALIFICACION_H

#include "DTFecha.h"

class Calificacion {
private:
    DTFecha fecha;
    int puntaje;

public:
    Calificacion(DTFecha fecha, int puntaje);
    ~Calificacion();
};

#endif
