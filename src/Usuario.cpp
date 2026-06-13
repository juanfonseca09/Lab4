#include "../include/Usuario.h"
#include "../include/Calificacion.h"
#include "../include/Reserva.h"
#include "../include/Viaje.h"

Usuario::Usuario(std::string nickname, std::string nombre, std::string contrasena, std::string email) {
    this->nickname = nickname;
    this->nombre = nombre;
    this->contrasena = contrasena;
    this->email = email;
}

Usuario::~Usuario() {
}

std::string Usuario::getNickname() {
    return nickname;
}

std::string Usuario::getNombre() {
    return nombre;
}

std::string Usuario::getContrasena() {
    return contrasena;
}

std::string Usuario::getEmail() {
    return email;
}

void Usuario::agregarCalificacionRealizada(Calificacion* calificacion) {
    if (calificacion != NULL) {
        calificacionesRealizadas.push_back(calificacion);
    }
}

void Usuario::agregarCalificacionRecibida(Calificacion* calificacion) {
    if (calificacion != NULL) {
        calificacionesRecibidas.push_back(calificacion);
    }
}

std::vector<Calificacion*> Usuario::getCalificacionesRealizadas() {
    return calificacionesRealizadas;
}

std::vector<Calificacion*> Usuario::getCalificacionesRecibidas() {
    return calificacionesRecibidas;
}

void Usuario::eliminarReferenciasCalificacionesDeViaje(Viaje* viaje) {
    std::vector<Calificacion*> nuevasRealizadas;

    for (unsigned int i = 0; i < calificacionesRealizadas.size(); i++) {
        Calificacion* c = calificacionesRealizadas[i];

        if (c != NULL &&
            c->getReserva() != NULL &&
            c->getReserva()->getViaje() == viaje) {
            continue;
        }

        nuevasRealizadas.push_back(c);
    }

    calificacionesRealizadas = nuevasRealizadas;

    std::vector<Calificacion*> nuevasRecibidas;

    for (unsigned int i = 0; i < calificacionesRecibidas.size(); i++) {
        Calificacion* c = calificacionesRecibidas[i];

        if (c != NULL &&
            c->getReserva() != NULL &&
            c->getReserva()->getViaje() == viaje) {
            continue;
        }

        nuevasRecibidas.push_back(c);
    }

    calificacionesRecibidas = nuevasRecibidas;
}

float Usuario::getCalifProm() {
    if (calificacionesRecibidas.empty()) {
        return 5;
    }

    float suma = 0;

    for (unsigned int i = 0; i < calificacionesRecibidas.size(); i++) {
        suma = suma + calificacionesRecibidas[i]->getPuntaje();
    }

    return suma / calificacionesRecibidas.size();
}