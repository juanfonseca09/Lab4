#include "../include/Fabrica.h"
#include "../include/ControladorCalificacion.h"
#include "../include/ControladorReserva.h"
#include "../include/ControladorUsuario.h"
#include "../include/ControladorFechaActual.h"

Fabrica* Fabrica::instancia = NULL;

Fabrica::Fabrica() {}

Fabrica* Fabrica::getInstance() {
    if (instancia == NULL) {
        instancia = new Fabrica();
    }
    return instancia;
}

IControladorFechaActual* Fabrica::getIControladorFechaActual() {
    return ControladorFechaActual::getInstance();
}

IControladorCalificacion* Fabrica::getIControladorCalificacion() {
    return ControladorCalificacion::getInstance();
}

IControladorReserva* Fabrica::getIControladorReserva() {
    return ControladorReserva::getInstance();
}

IControladorUsuario* Fabrica::getIControladorUsuario() {
    return ControladorUsuario::getInstance();
}
