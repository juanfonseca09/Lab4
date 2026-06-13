#include "../include/Viaje.h"
#include "../include/Vehiculo.h"
#include "../include/Reserva.h"
#include "../include/DTDetalleVehiculo.h"
#include "../include/DTDetalleReserva.h"

Viaje::Viaje(int codigo, Vehiculo* vehiculo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio) {
    this->codigo = codigo;
    this->vehiculo = vehiculo;
    this->fecha = fecha;
    this->origen = origen;
    this->destino = destino;
    this->asientosPublicados = asientosPublicados;
    this->precio = precio;
}

Viaje::~Viaje() {
    for (unsigned int i = 0; i < reservas.size(); i++) {
        delete reservas[i];
    }
}

int Viaje::getCodigo() {
    return codigo;
}

DTFecha Viaje::getFecha() {
    return fecha;
}

std::string Viaje::getOrigen() {
    return origen;
}

std::string Viaje::getDestino() {
    return destino;
}

int Viaje::getAsientosPublicados() {
    return asientosPublicados;
}

float Viaje::getPrecio() {
    return precio;
}

Vehiculo* Viaje::getVehiculo() {
    return vehiculo;
}

void Viaje::agregarReserva(Reserva* reserva) {
    if (reserva != NULL) {
        reservas.push_back(reserva);
    }
}

std::vector<Reserva*> Viaje::getReservas() {
    return reservas;
}

int Viaje::getAsientosReservados() {
    int total = 0;

    for (unsigned int i = 0; i < reservas.size(); i++) {
        total = total + reservas[i]->getAsientosReservados();
    }

    return total;
}

int Viaje::getAsientosDisponibles() {
    return asientosPublicados - getAsientosReservados();
}

bool Viaje::tieneDisponibilidad(int cantidadAsientos) {
    return cantidadAsientos > 0 && cantidadAsientos <= getAsientosDisponibles();
}

bool Viaje::tieneReservaDePasajero(std::string nicknamePasajero) {
    return buscarReservaDePasajero(nicknamePasajero) != NULL;
}

Reserva* Viaje::buscarReservaDePasajero(std::string nicknamePasajero) {
    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i]->perteneceAPasajero(nicknamePasajero)) {
            return reservas[i];
        }
    }

    return NULL;
}

bool Viaje::coincideCon(DTFecha fecha, std::string origen, std::string destino, int cantidadAsientos) {
    return this->fecha == fecha &&
           this->origen == origen &&
           this->destino == destino &&
           tieneDisponibilidad(cantidadAsientos);
}

DTDetalleViaje Viaje::getDetalle() {
    DTDetalleVehiculo detalleVehiculo(
        vehiculo->getMatricula(),
        vehiculo->getCapacidad(),
        vehiculo->getMarca(),
        vehiculo->getModelo(),
        vehiculo->getTipo()
    );

    std::vector<DTDetalleReserva> detallesReservas;

    for (unsigned int i = 0; i < reservas.size(); i++) {
        detallesReservas.push_back(reservas[i]->getDetalle());
    }

    return DTDetalleViaje(
        codigo,
        fecha,
        origen,
        destino,
        asientosPublicados,
        precio,
        detalleVehiculo,
        detallesReservas
    );
}