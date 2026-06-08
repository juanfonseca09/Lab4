#include "../include/Viaje.h"
#include "../include/DTDetalleVehiculo.h"
#include "../include/DTDetalleReserva.h"

Viaje::Viaje(int codigo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio) {
    this->codigo = codigo;
    this->fecha = fecha;
    this->origen = origen;
    this->destino = destino;
    this->asientosPublicados = asientosPublicados;
    this->precio = precio;
    this->vehiculo = NULL;
}

Viaje::Viaje(int codigo, DTFecha fecha, std::string origen, std::string destino, int asientosPublicados, float precio, Vehiculo* vehiculo) {
    this->codigo = codigo;
    this->fecha = fecha;
    this->origen = origen;
    this->destino = destino;
    this->asientosPublicados = asientosPublicados;
    this->precio = precio;
    this->vehiculo = vehiculo;
}

Viaje::~Viaje() {
    for (unsigned int i = 0; i < reservas.size(); i++) {
        delete reservas[i];
    }
}

int Viaje::getCodigo() const {
    return codigo;
}

DTFecha Viaje::getFecha() const {
    return fecha;
}

std::string Viaje::getOrigen() const {
    return origen;
}

std::string Viaje::getDestino() const {
    return destino;
}

int Viaje::getAsientosPublicados() const {
    return asientosPublicados;
}

float Viaje::getPrecio() const {
    return precio;
}

Vehiculo* Viaje::getVehiculo() const {
    return vehiculo;
}

int Viaje::getAsientosReservados() const {
    int total = 0;

    for (unsigned int i = 0; i < reservas.size(); i++) {
        total = total + reservas[i]->getAsientosReservados();
    }

    return total;
}

int Viaje::getAsientosDisponibles() const {
    return asientosPublicados - getAsientosReservados();
}

bool Viaje::tieneDisponibilidad(int cantidadAsientos) const {
    return cantidadAsientos > 0 && cantidadAsientos <= getAsientosDisponibles();
}

void Viaje::agregarReserva(Reserva* reserva) {
    if (reserva != NULL) {
        reservas.push_back(reserva);
    }
}

std::vector<Reserva*> Viaje::getReservas() const {
    return reservas;
}

bool Viaje::tieneReservaDePasajero(std::string nicknamePasajero) const {
    return buscarReservaDePasajero(nicknamePasajero) != NULL;
}

Reserva* Viaje::buscarReservaDePasajero(std::string nicknamePasajero) const {
    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i]->perteneceAPasajero(nicknamePasajero)) {
            return reservas[i];
        }
    }

    return NULL;
}

bool Viaje::coincideCon(DTFecha fecha, std::string origen, std::string destino, int cantidadAsientos) const {
    return this->fecha == fecha &&
           this->origen == origen &&
           this->destino == destino &&
           tieneDisponibilidad(cantidadAsientos);
}

DTDetalleViaje Viaje::getDetalle() const {
    DTDetalleVehiculo detalleVehiculo("", 0, "", "", Auto);

    if (vehiculo != NULL) {
        detalleVehiculo = DTDetalleVehiculo(
            vehiculo->getMatricula(),
            vehiculo->getCapacidad(),
            vehiculo->getMarca(),
            vehiculo->getModelo(),
            vehiculo->getTipo()
        );
    }

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