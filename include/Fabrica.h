#ifndef FABRICA_H
#define FABRICA_H

#include "IControladorCalificacion.h"
#include "IControladorFechaActual.h"
#include "IControladorReserva.h"
#include "IControladorUsuario.h"

class Fabrica {
private:
    static Fabrica* instancia;

    Fabrica();

public:
    static Fabrica* getInstance();

    IControladorCalificacion* getIControladorCalificacion();
    IControladorFechaActual* getIControladorFechaActual();
    IControladorReserva* getIControladorReserva();
    IControladorUsuario* getIControladorUsuario();
};

#endif
