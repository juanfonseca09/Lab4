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
#include <map>

ControladorReserva* ControladorReserva::instancia = NULL;

ControladorReserva::ControladorReserva() {
    // -1 = nadie eligio viaje
    codigoRecordado = -1;
}

ControladorReserva* ControladorReserva::getInstance() {
    if (instancia == NULL)
        instancia = new ControladorReserva();
    return instancia;
}

bool ControladorReserva::altaViaje(std::string matricula, DTFecha fecha, std::string origen, std::string destino, int asientos, float precio) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mviajes = ManejadorViaje::getInstance();
    Vehiculo* vehiculo = NULL;
    std::map<std::string, Usuario*> usuarios = mu->getUsuarios();
    std::map<std::string, Usuario*>::iterator it;
    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Conductor* conductor = dynamic_cast<Conductor*>(it->second);
        if (conductor != NULL) {
            vehiculo = conductor->buscarVehiculo(matricula);
            if (vehiculo != NULL)
                break;
        }
    }
    if (vehiculo == NULL)
        return false;
    if (asientos > vehiculo->getCapacidad())
        return false;
    if (vehiculo->hayViajeFecha(fecha))
        return false;
    Viaje* viaje = mviajes->createViaje( vehiculo, fecha, origen, destino, asientos, precio);
    vehiculo->agregarViaje(viaje);
    return true;
}

bool ControladorReserva::generarReserva(std::string nickname, int codigo, int asientos) {
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    ManejadorReserva* mr = ManejadorReserva::getInstance();
    Usuario* u = mu->find(nickname);
    Pasajero* pasajero = dynamic_cast<Pasajero*>(u);
    if (pasajero == NULL)
        return false;
    Viaje* viaje = mv->find(codigo);
    if (viaje == NULL)
        return false;
    if (!viaje->tieneDisponibilidad(asientos))
        return false;
    if (viaje->tieneReservaDePasajero(nickname))
        return false;
    DTFecha fechaActual = ControladorFechaActual::getInstance()->getFecha();
    Reserva* reserva = new Reserva(asientos,fechaActual,pasajero,viaje);
    viaje->agregarReserva(reserva);
    pasajero->agregarReserva(reserva);
    mr->agregarReserva(reserva);
    return true;
}

std::set<std::string> ControladorReserva::listarPasajeros() {
    std::set<std::string> resultado;
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    std::map<std::string, Usuario*> usuarios = mu->getUsuarios();
    std::map<std::string, Usuario*>::iterator it;
    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Pasajero* p = dynamic_cast<Pasajero*>(it->second);
        if (p != NULL)
            resultado.insert(p->getNickname());
    }
    return resultado;
}

std::vector<DTConsultaViaje> ControladorReserva::consultarViajes( DTFecha fecha,std::string origen,std::string destino, int asientos
) {
    std::vector<DTConsultaViaje> resultado;
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    std::map<int, Viaje*> viajes = mv->getViajes();
    std::map<int, Viaje*>::iterator it;
    for (it = viajes.begin(); it != viajes.end(); ++it) {
        Viaje* viaje = it->second;
        if (!viaje->coincideCon(fecha, origen, destino,asientos))
            continue;
        Vehiculo* vehiculo = viaje->getVehiculo();
        DTConsultaViaje dt(viaje->getCodigo(),vehiculo->getMarca(),vehiculo->getModelo(),vehiculo->getConductor()->getNickname(),vehiculo->getConductor()->getCalifProm(),viaje->getPrecio() * asientos);
        resultado.push_back(dt);
    }
    return resultado;
}

std::vector<DTListarViaje> ControladorReserva::listarViajes() {
    std::vector<DTListarViaje> resultado;
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    std::map<int, Viaje*> viajes = mv->getViajes();
    std::map<int, Viaje*>::iterator it;
    for (it = viajes.begin(); it != viajes.end(); ++it) {
        Viaje* v = it->second;
        resultado.push_back(DTListarViaje(v->getCodigo(),v->getFecha(),v->getOrigen(),v->getDestino(),v->getVehiculo()->getConductor()->getNickname()));
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
    if (codigoRecordado == -1)
        return;
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    Viaje* viaje = mv->find(codigoRecordado);
    if (viaje == NULL)
        return;
    viaje->getVehiculo()->eliminarViaje(codigoRecordado);
    mv->eliminarViaje(codigoRecordado);
    codigoRecordado = -1;
}

DTVehiculosConductor ControladorReserva::listarVehiculosConductor(std::string nickname) {
    std::vector<DTDetalleVehiculo> resultado;
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Usuario* u = mu->find(nickname);
    Conductor* c = dynamic_cast<Conductor*>(u);
    if(c == NULL)
        return DTVehiculosConductor(resultado);
    std::vector<Vehiculo*> vehiculos = c->getVehiculos();
    for(unsigned i = 0; i < vehiculos.size(); i++) {
        resultado.push_back(DTDetalleVehiculo(vehiculos[i]->getMatricula(),vehiculos[i]->getCapacidad(),vehiculos[i]->getMarca(),vehiculos[i]->getModelo(),vehiculos[i]->getTipo()));
    }
    return DTVehiculosConductor(resultado);
}