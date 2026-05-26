#ifndef FABRICA_H
#define FABRICA_H

#include "IControladorFechaActual.h"

class Fabrica {
private:
    static Fabrica* instancia;

    Fabrica();

public:
    static Fabrica* getInstance();

    IControladorFechaActual* getIControladorFechaActual();
};

#endif
