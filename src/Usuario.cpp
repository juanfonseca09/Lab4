#include "../include/Usuario.h"
#include "../include/Calificacion.h"

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

float Usuario::getCalifProm() const {
    if (recibidas.size() == 0) return 0;
    int suma = 0;
    for (unsigned  i = 0; i < recibidas.size(); i++) {
        suma += recibidas[i]->getPuntaje();
    }
    return (float)suma / recibidas.size();
}

void Usuario::agregarCalificacionRealizada(Calificacion* c) {
    realizadas.push_back(c);
}

void Usuario::agregarCalificacionRecibida(Calificacion* c) {
    recibidas.push_back(c);
}

std::vector<Calificacion*> Usuario::getRealizadas() const {
    return realizadas;
}

std::vector<Calificacion*> Usuario::getRecibidas() const {
    return recibidas;
}