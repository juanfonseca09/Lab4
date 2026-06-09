#include "../include/Calificacion.h"
#include "../include/Usuario.h"
#include "../include/Reserva.h"


Calificacion::Calificacion(DTFecha fecha, int puntaje, Usuario* evaluador, Usuario* evaluado, Reserva* reserva) {
    this->fecha = fecha;
    this->puntaje = puntaje;
    this->evaluador = evaluador;
    this->evaluado = evaluado;
    this->reserva = reserva;
}

Calificacion::~Calificacion() {
}

DTFecha Calificacion::getFecha() const {
    return fecha;
}

int Calificacion::getPuntaje() const {
    return puntaje;
}

Usuario* Calificacion::getEvaluador() const {
    return evaluador;
}

Usuario* Calificacion::getEvaluado() const {
    return evaluado;
}

Reserva* Calificacion::getReserva() const {
    return reserva;
}

bool Calificacion::esDePara(std::string nicknameEvaluador, std::string nicknameEvaluado) const {
    if (evaluador == NULL || evaluado == NULL) {
        return false;
    }
    return evaluador->getNickname() == nicknameEvaluador && evaluado->getNickname() == nicknameEvaluado;
}