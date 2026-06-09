#include "../include/ManejadorUsuario.h"
#include "../include/Usuario.h"

ManejadorUsuario* ManejadorUsuario::instancia = NULL;

ManejadorUsuario::ManejadorUsuario() {
}

ManejadorUsuario* ManejadorUsuario::getInstance() {
    if (instancia == NULL)
        instancia = new ManejadorUsuario();
    return instancia;
}

void ManejadorUsuario::agregarUsuario(Usuario* u) {
    if (u != NULL)
        usuarios[u->getNickname()] = u;
}

Usuario* ManejadorUsuario::find(std::string nickname) {
    std::map<std::string, Usuario*>::iterator it = usuarios.find(nickname);
    if (it == usuarios.end())
        return NULL;
    return it->second;
}

bool ManejadorUsuario::existeUsuario(std::string nickname) {
    return find(nickname) != NULL;
}

std::map<std::string, Usuario*> ManejadorUsuario::getUsuarios() {
    return usuarios;
}