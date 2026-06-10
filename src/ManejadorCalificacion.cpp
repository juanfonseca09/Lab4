#include "../include/ManejadorCalificacion.h"
#include "../include/Calificacion.h"

ManejadorCalificacion* ManejadorCalificacion::instancia = NULL;

ManejadorCalificacion::ManejadorCalificacion() {
}

ManejadorCalificacion::~ManejadorCalificacion() {
    while (!calificaciones.empty())
    {
        Calificacion* a_borrar = calificaciones.back();
        calificaciones.pop_back();
        delete a_borrar;
    }
}

ManejadorCalificacion* ManejadorCalificacion::getInstance() {
    if (instancia == NULL)
        instancia = new ManejadorCalificacion();
    return instancia;
}

void ManejadorCalificacion::agregarCalificacion(Calificacion* c) {
    calificaciones.push_back(c);
}

std::vector<Calificacion*> ManejadorCalificacion::getCalificaciones() {
    return calificaciones;
}