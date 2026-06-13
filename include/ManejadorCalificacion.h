#ifndef MANEJADOR_CALIFICACION_H
#define MANEJADOR_CALIFICACION_H

#include "Calificacion.h"

#include <vector>

class Viaje;

class ManejadorCalificacion {
private:
    static ManejadorCalificacion* instancia;

    std::vector<Calificacion*> calificaciones;

    ManejadorCalificacion();

public:
    static ManejadorCalificacion* getInstance();

    void agregarCalificacion(Calificacion* calificacion);

    std::vector<Calificacion*> getCalificaciones();

    void eliminarReferenciasCalificacionesDeViaje(Viaje* viaje);
};

#endif