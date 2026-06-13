#include "../include/ManejadorCalificacion.h"
#include "../include/Reserva.h"
#include "../include/Viaje.h"

ManejadorCalificacion* ManejadorCalificacion::instancia = NULL;

ManejadorCalificacion::ManejadorCalificacion() {
}

ManejadorCalificacion* ManejadorCalificacion::getInstance() {
    if (instancia == NULL) {
        instancia = new ManejadorCalificacion();
    }

    return instancia;
}

void ManejadorCalificacion::agregarCalificacion(Calificacion* calificacion) {
    if (calificacion != NULL) {
        calificaciones.push_back(calificacion);
    }
}

std::vector<Calificacion*> ManejadorCalificacion::getCalificaciones() {
    return calificaciones;
}

void ManejadorCalificacion::eliminarReferenciasCalificacionesDeViaje(Viaje* viaje) {
    std::vector<Calificacion*> nuevasCalificaciones;

    for (unsigned int i = 0; i < calificaciones.size(); i++) {
        Calificacion* c = calificaciones[i];

        if (c != NULL &&
            c->getReserva() != NULL &&
            c->getReserva()->getViaje() == viaje) {
            continue;
        }

        nuevasCalificaciones.push_back(c);
    }

    calificaciones = nuevasCalificaciones;
}