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
    if (mu->existeUsuario(nickname))
        return false;
    Pasajero* p = new Pasajero(nickname, nombre, contrasena, email, ci);
    mu->agregarUsuario(p);
    return true;
}

bool ControladorUsuario::altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    if (mu->existeUsuario(nickname))
        return false;
    Conductor* c = new Conductor(nickname, nombre, contrasena, email, libretas);
    mu->agregarUsuario(c);
    return true;
}

int ControladorUsuario::registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorVehiculo* mv = ManejadorVehiculo::getInstance();
    Usuario* u = mu->find(nickname);
    Conductor* c = dynamic_cast<Conductor*>(u);
    if (c == NULL)
        return -2;
    if (mv->existeVehiculo(matricula))
        return -1;
    if (!c->puedeConducir(tipo))
        return -2;
    Vehiculo* v = new Vehiculo(matricula, capacidad, marca, modelo, tipo, c);
    c->agregarVehiculo(v);
    mv->agregarVehiculo(v);
    return 0;
}