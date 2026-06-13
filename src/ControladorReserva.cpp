#include "../include/ManejadorUsuario.h"
#include "../include/ManejadorViaje.h"
#include "../include/ManejadorReserva.h"
#include "../include/Pasajero.h"
#include "../include/Reserva.h"
#include "../include/ControladorFechaActual.h"
#include "../include/DTConsultaViaje.h"
#include "../include/Conductor.h"
#include "../include/ControladorReserva.h"
#include "../include/Vehiculo.h"
#include "../include/Viaje.h"
#include "../include/ManejadorCalificacion.h"

#include <map>
#include <algorithm>

ControladorReserva* ControladorReserva::instancia = NULL;

static bool compararConsultaViaje(DTConsultaViaje a, DTConsultaViaje b) {
    if (a.getPrecioTotal() != b.getPrecioTotal()) {
        return a.getPrecioTotal() < b.getPrecioTotal();
    }

    return a.getCalificacionProm() > b.getCalificacionProm();
}

ControladorReserva::ControladorReserva() {
    codigoRecordado = -1;
}

ControladorReserva* ControladorReserva::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorReserva();
    }

    return instancia;
}

bool ControladorReserva::altaViaje(std::string matricula, DTFecha fecha, std::string origen, std::string destino, int asientos, float precio) {
    if (matricula == "" || origen == "" || destino == "" || asientos <= 0 || precio <= 0) {
        return false;
    }

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mviajes = ManejadorViaje::getInstance();
    Vehiculo* vehiculo = NULL;

    std::map<std::string, Usuario*> usuarios = mu->getUsuarios();
    std::map<std::string, Usuario*>::iterator it;

    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Conductor* conductor = dynamic_cast<Conductor*>(it->second);

        if (conductor != NULL) {
            vehiculo = conductor->buscarVehiculo(matricula);

            if (vehiculo != NULL) {
                break;
            }
        }
    }

    if (vehiculo == NULL) {
        return false;
    }

    if (asientos > vehiculo->getCapacidad()) {
        return false;
    }

    if (vehiculo->hayViajeFecha(fecha)) {
        return false;
    }

    Viaje* viaje = mviajes->createViaje(vehiculo, fecha, origen, destino, asientos, precio);
    vehiculo->agregarViaje(viaje);

    return true;
}

bool ControladorReserva::generarReserva(std::string nickname, int codigo, int asientos) {
    if (nickname == "" || asientos <= 0) {
        return false;
    }

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    ManejadorReserva* mr = ManejadorReserva::getInstance();

    Viaje* viaje = mv->find(codigo);

    if (viaje == NULL) {
        return false;
    }

    if (viaje->tieneReservaDePasajero(nickname)) {
        return false;
    }

    if (!viaje->tieneDisponibilidad(asientos)) {
        return false;
    }

    Usuario* u = mu->find(nickname);
    Pasajero* pasajero = dynamic_cast<Pasajero*>(u);

    if (pasajero == NULL) {
        return false;
    }

    DTFecha fechaActual = ControladorFechaActual::getInstance()->getFecha();
    Reserva* reserva = new Reserva(asientos, fechaActual, pasajero, viaje);

    mr->agregarReserva(reserva);
    viaje->agregarReserva(reserva);
    pasajero->agregarReserva(reserva);

    return true;
}

std::set<std::string> ControladorReserva::listarPasajeros() {
    std::set<std::string> resultado;

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    std::map<std::string, Usuario*> usuarios = mu->getUsuarios();
    std::map<std::string, Usuario*>::iterator it;

    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Pasajero* p = dynamic_cast<Pasajero*>(it->second);

        if (p != NULL) {
            resultado.insert(p->getNickname());
        }
    }

    return resultado;
}

std::vector<DTConsultaViaje> ControladorReserva::consultarViajes(DTFecha fecha, std::string origen, std::string destino, int asientos) {
    std::vector<DTConsultaViaje> resultado;

    ManejadorViaje* mv = ManejadorViaje::getInstance();
    std::map<int, Viaje*> viajes = mv->getViajes();
    std::map<int, Viaje*>::iterator it;

    for (it = viajes.begin(); it != viajes.end(); ++it) {
        Viaje* viaje = it->second;

        if (!viaje->coincideCon(fecha, origen, destino, asientos)) {
            continue;
        }

        Vehiculo* vehiculo = viaje->getVehiculo();
        Conductor* conductor = vehiculo->getConductor();

        DTConsultaViaje dt(
            viaje->getCodigo(),
            vehiculo->getMarca(),
            vehiculo->getModelo(),
            conductor->getNombre(),
            conductor->getCalifProm(),
            viaje->getPrecio() * asientos
        );

        resultado.push_back(dt);
    }

    std::sort(resultado.begin(), resultado.end(), compararConsultaViaje);

    return resultado;
}

std::vector<DTListarViaje> ControladorReserva::listarViajes() {
    std::vector<DTListarViaje> resultado;

    ManejadorViaje* mv = ManejadorViaje::getInstance();
    std::map<int, Viaje*> viajes = mv->getViajes();
    std::map<int, Viaje*>::iterator it;

    for (it = viajes.begin(); it != viajes.end(); ++it) {
        Viaje* v = it->second;

        resultado.push_back(
            DTListarViaje(
                v->getCodigo(),
                v->getFecha(),
                v->getOrigen(),
                v->getDestino(),
                v->getVehiculo()->getConductor()->getNickname()
            )
        );
    }

    return resultado;
}

DTDetalleViaje ControladorReserva::detalleViaje(int codigo) {
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    Viaje* viaje = mv->find(codigo);

    codigoRecordado = codigo;

    return viaje->getDetalle();
}

void ControladorReserva::cancelarEliminarViaje() {
    codigoRecordado = -1;
}

void ControladorReserva::eliminarViaje() {
    if (codigoRecordado == -1) {
        return;
    }

    ManejadorViaje* mv = ManejadorViaje::getInstance();
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorReserva* mr = ManejadorReserva::getInstance();
    ManejadorCalificacion* mc = ManejadorCalificacion::getInstance();

    Viaje* viaje = mv->find(codigoRecordado);

    if (viaje == NULL) {
        codigoRecordado = -1;
        return;
    }

    Vehiculo* vehiculo = viaje->getVehiculo();

    
    mu->eliminarReferenciasDeViaje(viaje);
    mr->eliminarReferenciasReservasDeViaje(viaje);
    mc->eliminarReferenciasCalificacionesDeViaje(viaje);

    if (vehiculo != NULL) {
        vehiculo->eliminarViaje(codigoRecordado);
    }

  
    mv->eliminarViaje(codigoRecordado);

    codigoRecordado = -1;
}

std::vector<DTVehiculosConductor> ControladorReserva::listarVehiculosConductor(std::string nickname) {
    std::vector<DTVehiculosConductor> resultado;

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Usuario* u = mu->find(nickname);
    Conductor* c = dynamic_cast<Conductor*>(u);

    if (c == NULL) {
        return resultado;
    }

    std::vector<Vehiculo*> vehiculos = c->getVehiculos();

    for (unsigned int i = 0; i < vehiculos.size(); i++) {
        resultado.push_back(
            DTVehiculosConductor(
                vehiculos[i]->getMatricula(),
                vehiculos[i]->getMarca(),
                vehiculos[i]->getCapacidad()
            )
        );
    }

    return resultado;
}