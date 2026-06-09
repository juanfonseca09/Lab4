#ifndef MANEJADOR_USUARIO_H
#define MANEJADOR_USUARIO_H

#include <map>
#include <string>

class Usuario;

class ManejadorUsuario {
private:
    static ManejadorUsuario* instancia;
    std::map<std::string, Usuario*> usuarios;
    ManejadorUsuario();
public:
    static ManejadorUsuario* getInstance();
    void agregarUsuario(Usuario* u);
    Usuario* find(std::string nickname);
    bool existeUsuario(std::string nickname);
    std::map<std::string, Usuario*> getUsuarios();
};

#endif