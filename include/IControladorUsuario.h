#ifndef ICONTROLADOR_USUARIO_H
#define ICONTROLADOR_USUARIO_H

#include <string>
#include <set>

#include "TipoLibreta.h"
#include "TipoVehiculo.h"

class IControladorUsuario {
public:
    virtual ~IControladorUsuario(){}
    virtual bool altaPasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci) = 0;
    virtual bool altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas) = 0;
    virtual int registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) = 0;
};

#endif