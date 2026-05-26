#include "../include/Fabrica.h"
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
