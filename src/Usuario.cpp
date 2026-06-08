#include "../include/Usuario.h"

Usuario::Usuario(std::string nickname, std::string nombre, std::string contrasena, std::string email) {
    this->nickname = nickname;
    this->nombre = nombre;
    this->contrasena = contrasena;
    this->email = email;
}

Usuario::~Usuario() {
}

std::string Usuario::getNickname() const {
    return nickname;
}

std::string Usuario::getNombre() const {
    return nombre;
}

std::string Usuario::getContrasena() const {
    return contrasena;
}

std::string Usuario::getEmail() const {
    return email;
}