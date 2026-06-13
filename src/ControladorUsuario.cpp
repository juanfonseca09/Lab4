#include "../include/ControladorUsuario.h"
#include "../include/ManejadorUsuario.h"

ControladorUsuario* ControladorUsuario::instancia = NULL;

ControladorUsuario::ControladorUsuario() {
}

ControladorUsuario* ControladorUsuario::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorUsuario();
    }

    return instancia;
}

bool ControladorUsuario::altaPasajero(
    std::string nickname,
    std::string nombre,
    std::string contrasena,
    std::string email,
    std::string ci
) {
    if (nickname == "" || nombre == "" || email == "" || ci == "") {
        return false;
    }

    if (contrasena.length() < 8) {
        return false;
    }

    return ManejadorUsuario::getInstance()->altaPasajero(
        nickname,
        nombre,
        contrasena,
        email,
        ci
    );
}

bool ControladorUsuario::altaConductor(
    std::string nickname,
    std::string nombre,
    std::string contrasena,
    std::string email,
    std::set<TipoLibreta> libretas
) {
    if (nickname == "" || nombre == "" || email == "") {
        return false;
    }

    if (contrasena.length() < 8) {
        return false;
    }

    if (libretas.empty()) {
        return false;
    }

    return ManejadorUsuario::getInstance()->altaConductor(
        nickname,
        nombre,
        contrasena,
        email,
        libretas
    );
}

int ControladorUsuario::registrarVehiculo(
    std::string nickname,
    std::string matricula,
    int capacidad,
    std::string marca,
    std::string modelo,
    TipoVehiculo tipo
) {
    if (matricula == "" || marca == "" || modelo == "" || capacidad <= 0) {
        return -3;
    }

    return ManejadorUsuario::getInstance()->registrarVehiculo(
        nickname,
        matricula,
        capacidad,
        marca,
        modelo,
        tipo
    );
}