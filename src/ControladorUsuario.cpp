#include "../include/ControladorUsuario.h"

ControladorUsuario* ControladorUsuario::instancia = NULL;

ControladorUsuario* ControladorUsuario::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorUsuario();
    }
    return instancia;
}