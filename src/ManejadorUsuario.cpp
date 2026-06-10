#include "../include/ManejadorUsuario.h"
#include "../include/Usuario.h"
#include "../include/Conductor.h"
#include "../include/Pasajero.h"
#include "../include/Vehiculo.h"
#include "../include/ManejadorVehiculo.h"

ManejadorUsuario* ManejadorUsuario::instancia = NULL;

ManejadorUsuario::ManejadorUsuario() {
}

ManejadorUsuario::~ManejadorUsuario() {
    while (!usuarios.empty())
    {
        std::map<std::string, Usuario*>::iterator it = usuarios.end();
        --it;
        Usuario* a_borrar = it->second;
        usuarios.erase(it);
        delete a_borrar;
    }
}

ManejadorUsuario* ManejadorUsuario::getInstance() {
    if (instancia == NULL)
        instancia = new ManejadorUsuario();
    return instancia;
}

bool ManejadorUsuario::altaPasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci) {
    if (find(nickname) != NULL)
        return false;
    Pasajero* p = new Pasajero(nickname, nombre, contrasena, email, ci);
    agregarUsuario(p);
    return true;

}

bool ManejadorUsuario::altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas) {
    if (find(nickname) != NULL )
        return false;
    Conductor* c = new Conductor(nickname, nombre, contrasena, email, libretas);
    agregarUsuario(c);
    return true;
}

int ManejadorUsuario::registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo) {
    if (existeVehiculo(matricula))
        return -1;
    Usuario* u = find(nickname);
    Conductor* c = dynamic_cast<Conductor*>(u); // Si u no es conductor devuelve NULL
    if (c == NULL || !c->puedeConducir(tipo))
        return -2;
    Vehiculo* v = new Vehiculo(matricula, capacidad, marca, modelo, tipo, c);
    c->agregarVehiculo(v);
    agregarVehiculo(v);
    return 0;
}

void ManejadorUsuario::agregarUsuario(Usuario* u) {
    if (u != NULL)
        usuarios[u->getNickname()] = u;
}

void ManejadorUsuario::agregarVehiculo(Vehiculo* v) {
    if (v != NULL)
        vehiculos[v->getMatricula()] = v;
}

Vehiculo* ManejadorUsuario::findVehiculo(std::string matricula) {
    std::map<std::string, Vehiculo*>::iterator it;
    it = vehiculos.find(matricula);
    if (it == vehiculos.end())
        return NULL;
    return it->second;
}

bool ManejadorUsuario::existeVehiculo(std::string matricula) {
    return findVehiculo(matricula) != NULL;
}

std::map<std::string, Vehiculo*> ManejadorUsuario::getVehiculos() {
    return vehiculos;
}

Usuario* ManejadorUsuario::find(std::string nickname) {
    std::map<std::string, Usuario*>::iterator it = usuarios.find(nickname);
    if (it == usuarios.end())
        return NULL;
    return it->second;
}


std::map<std::string, Usuario*> ManejadorUsuario::getUsuarios() {
    return usuarios;
}