#ifndef MANEJADOR_USUARIO_H
#define MANEJADOR_USUARIO_H

#include <map>
#include <string>
#include <set>

#include "Conductor.h"

class Usuario;

class ManejadorUsuario {
private:
    static ManejadorUsuario* instancia;
    std::map<std::string, Usuario*> usuarios;
    ManejadorUsuario();
public:
    ~ManejadorUsuario();
    static ManejadorUsuario* getInstance();
    bool altaPasajero(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::string ci);
    bool altaConductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libretas);
    int registrarVehiculo(std::string nickname, std::string matricula, int capacidad, std::string marca, std::string modelo, TipoVehiculo tipo);
    void agregarUsuario(Usuario* u);
    Usuario* find(std::string nickname);
    std::map<std::string, Usuario*> getUsuarios();
};

#endif