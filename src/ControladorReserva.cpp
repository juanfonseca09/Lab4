#include "../include/ControladorReserva.h"

ControladorReserva* ControladorReserva::instancia = NULL;

ControladorReserva* ControladorReserva::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorReserva();
    }
    return instancia;
}