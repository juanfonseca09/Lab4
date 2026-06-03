#include "../include/ControladorCalificacion.h"

ControladorCalificacion* ControladorCalificacion::instancia = NULL;

ControladorCalificacion* ControladorCalificacion::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorCalificacion();
    }
    return instancia;
}