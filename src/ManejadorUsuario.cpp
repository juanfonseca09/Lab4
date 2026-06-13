#include "../include/ManejadorUsuario.h"
#include "../include/Pasajero.h"
#include "../include/Conductor.h"
#include "../include/Vehiculo.h"
#include "../include/Viaje.h"

ManejadorUsuario* ManejadorUsuario::instancia = NULL;

ManejadorUsuario::ManejadorUsuario() {
}

ManejadorUsuario* ManejadorUsuario::getInstance() {
    if (instancia == NULL) {
        instancia = new ManejadorUsuario();
    }

    return instancia;
}

void ManejadorUsuario::agregarUsuario(Usuario* usuario) {
    if (usuario != NULL) {
        usuarios[usuario->getNickname()] = usuario;
    }
}

Usuario* ManejadorUsuario::find(std::string nickname) {
    std::map<std::string, Usuario*>::iterator it = usuarios.find(nickname);

    if (it == usuarios.end()) {
        return NULL;
    }

    return it->second;
}

bool ManejadorUsuario::existeNickname(std::string nickname) {
    return find(nickname) != NULL;
}

std::map<std::string, Usuario*> ManejadorUsuario::getUsuarios() {
    return usuarios;
}

bool ManejadorUsuario::altaPasajero(
    std::string nickname,
    std::string nombre,
    std::string contrasena,
    std::string email,
    std::string ci
) {
    if (existeNickname(nickname)) {
        return false;
    }

    Pasajero* pasajero = new Pasajero(nickname, nombre, contrasena, email, ci);
    agregarUsuario(pasajero);

    return true;
}

bool ManejadorUsuario::altaConductor(
    std::string nickname,
    std::string nombre,
    std::string contrasena,
    std::string email,
    std::set<TipoLibreta> libretas
) {
    if (existeNickname(nickname)) {
        return false;
    }

    Conductor* conductor = new Conductor(nickname, nombre, contrasena, email, libretas);
    agregarUsuario(conductor);

    return true;
}

bool ManejadorUsuario::existeMatricula(std::string matricula) {
    std::map<std::string, Usuario*>::iterator it;

    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Conductor* conductor = dynamic_cast<Conductor*>(it->second);

        if (conductor != NULL && conductor->buscarVehiculo(matricula) != NULL) {
            return true;
        }
    }

    return false;
}

int ManejadorUsuario::registrarVehiculo(
    std::string nickname,
    std::string matricula,
    int capacidad,
    std::string marca,
    std::string modelo,
    TipoVehiculo tipo
) {
    Usuario* usuario = find(nickname);
    Conductor* conductor = dynamic_cast<Conductor*>(usuario);

    if (conductor == NULL) {
        return -3;
    }

    if (matricula == "" || capacidad <= 0 || marca == "" || modelo == "") {
        return -3;
    }

    if (existeMatricula(matricula)) {
        return -1;
    }

    if (!conductor->puedeConducir(tipo)) {
        return -2;
    }

    Vehiculo* vehiculo = new Vehiculo(matricula, capacidad, marca, modelo, tipo);

    bool agregado = conductor->agregarVehiculo(vehiculo);

    if (!agregado) {
        delete vehiculo;
        return -2;
    }

    return 0;
}

void ManejadorUsuario::eliminarReferenciasDeViaje(Viaje* viaje) {
    std::map<std::string, Usuario*>::iterator it;

    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Usuario* usuario = it->second;

        if (usuario != NULL) {
            usuario->eliminarReferenciasCalificacionesDeViaje(viaje);
        }

        Pasajero* pasajero = dynamic_cast<Pasajero*>(usuario);

        if (pasajero != NULL) {
            pasajero->eliminarReferenciaReservaDeViaje(viaje);
        }
    }
}