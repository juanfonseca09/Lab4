#include "../include/Calificacion.h"
#include "../include/Usuario.h"

Calificacion::Calificacion(DTFecha fecha, int puntaje, Usuario* evaluador, Usuario* evaluado, Reserva* reserva) {
    this->fecha = fecha;
    this->puntaje = puntaje;
    this->evaluador = evaluador;
    this->evaluado = evaluado;
    this->reserva = reserva;
}

Calificacion::~Calificacion() {
}

DTFecha Calificacion::getFecha() {
    return fecha;
}

int Calificacion::getPuntaje() {
    return puntaje;
}

Usuario* Calificacion::getEvaluador() {
    return evaluador;
}

Usuario* Calificacion::getEvaluado() {
    return evaluado;
}

Reserva* Calificacion::getReserva() {
    return reserva;
}

bool Calificacion::esDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) {
    if (evaluador == NULL || evaluado == NULL) {
        return false;
    }

    return evaluador->getNickname() == nicknameEvaluador &&
           evaluado->getNickname() == nicknameEvaluado;
}