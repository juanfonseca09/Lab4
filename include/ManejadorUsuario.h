#ifndef MANEJADOR_USUARIO_H
#define MANEJADOR_USUARIO_H

#include <map>
#include <string>
#include <set>
#include "Conductor.h"
#include "Vehiculo.h"

class Usuario;

class ManejadorUsuario {
private:
    static ManejadorUsuario* instancia;
    std::map<std::string, Usuario*> usuarios;
    std::map<std::string, Vehiculo*> vehiculos;
    ManejadorUsuario();
public:
    ~ManejadorUsuario();
    static ManejadorUsuario* getInstance();
    bool altaPasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci);
    bool altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas);
    int registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo);
    std::map<std::string, Vehiculo*> getVehiculos();
    void agregarUsuario(Usuario* u);
    void agregarVehiculo(Vehiculo* v);
    Vehiculo* findVehiculo(std::string matricula);
    bool existeVehiculo(std::string matricula);
    Usuario* find(std::string nickname);
    std::map<std::string, Usuario*> getUsuarios();
};

#endif