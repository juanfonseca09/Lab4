#include "../include/ControladorUsuario.h"
#include "../include/ManejadorUsuario.h"
#include "../include/ManejadorVehiculo.h"
#include "../include/Usuario.h"
#include "../include/Pasajero.h"
#include "../include/Conductor.h"
#include "../include/Vehiculo.h"

ControladorUsuario* ControladorUsuario::instancia = NULL;

ControladorUsuario::ControladorUsuario() {
}

ControladorUsuario* ControladorUsuario::getInstance() {
    if (instancia == NULL)
        instancia = new ControladorUsuario();
    return instancia;
}

bool ControladorUsuario::altaPasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    return mu->altaPasajero(nickname, nombre, contrasena, email, ci);
}

bool ControladorUsuario::altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    return mu->altaConductor(nickname, nombre, contrasena, email, libretas);
}

int ControladorUsuario::registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    return mu->registrarVehiculo(nickname, matricula, capacidad, marca, modelo, tipo);
}