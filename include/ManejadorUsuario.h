#ifndef MANEJADOR_USUARIO_H
#define MANEJADOR_USUARIO_H

#include "Usuario.h"
#include "TipoLibreta.h"
#include "TipoVehiculo.h"
#include "DTFecha.h"

#include <string>
#include <map>
#include <set>

class Viaje;

class ManejadorUsuario {
private:
    static ManejadorUsuario* instancia;
    std::map<std::string, Usuario*> usuarios;

    ManejadorUsuario();

public:
    static ManejadorUsuario* getInstance();

    void agregarUsuario(Usuario* usuario);

    Usuario* find(std::string nickname);
    bool existeNickname(std::string nickname);

    std::map<std::string, Usuario*> getUsuarios();

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

    bool existeMatricula(std::string matricula);

    void eliminarReferenciasDeViaje(Viaje* viaje);
};

#endif