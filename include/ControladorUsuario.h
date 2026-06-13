#ifndef CONTROLADOR_USUARIO_H
#define CONTROLADOR_USUARIO_H

#include "IControladorUsuario.h"

class ControladorUsuario : public IControladorUsuario {
private:
    static ControladorUsuario* instancia;

    ControladorUsuario();

public:
    static ControladorUsuario* getInstance();

    bool altaPasajero(
        std::string nickname,
        std::string nombre,
        std::string contrasena,
        std::string email,
        std::string ci
    );

    bool altaConductor(
        std::string nickname,
        std::string nombre,
        std::string contrasena,
        std::string email,
        std::set<TipoLibreta> libretas
    );

    int registrarVehiculo(
        std::string nickname,
        std::string matricula,
        int capacidad,
        std::string marca,
        std::string modelo,
        TipoVehiculo tipo
    );
};

#endif