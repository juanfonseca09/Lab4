#include "../include/ControladorCalificacion.h"
#include "../include/ManejadorUsuario.h"
#include "../include/ManejadorViaje.h"
#include "../include/Usuario.h"
#include "../include/Pasajero.h"
#include "../include/Reserva.h"
#include "../include/Viaje.h"
#include "../include/Vehiculo.h"
#include "../include/Conductor.h"
#include <map>

ControladorCalificacion* ControladorCalificacion::instancia = NULL;

ControladorCalificacion::ControladorCalificacion() {
    nicknameRecordado = "";
    codigoRecordado = -1;
}

ControladorCalificacion* ControladorCalificacion::getInstance() {
    if (instancia == NULL) {
        instancia = new ControladorCalificacion();
    }
    return instancia;
}

std::vector<DTUsuario> ControladorCalificacion::listarUsuarios() {
    std::vector<DTUsuario> resultado;
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    std::map<std::string, Usuario*> usuarios = mu->getUsuarios();
    std::map<std::string, Usuario*>::iterator it;
    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Usuario* u = it->second;
        resultado.push_back(DTUsuario(u->getNickname(), u->getNombre()));
    }
    return resultado;
}

std::vector<DTListarViaje> ControladorCalificacion::listarViajes(std::string nickname) {
    std::vector<DTListarViaje> resultado;
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Usuario* u = mu->find(nickname);
    Pasajero* pasajero = dynamic_cast<Pasajero*>(u);
    if (pasajero != NULL) {
        std::vector<Reserva*> reservas = pasajero->getReservas();
        for (unsigned  i = 0; i < reservas.size(); i++) {
            Viaje* v = reservas[i]->getViaje();
            resultado.push_back(DTListarViaje(v->getCodigo(), v->getFecha(), v->getOrigen(), v->getDestino(), v->getVehiculo()->getConductor()->getNickname()));
        }
    }
    nicknameRecordado = nickname;
    return resultado;
}

std::vector<DTUsuarioViaje> ControladorCalificacion::listarUsuariosViaje(int codigo) {
    std::vector<DTUsuarioViaje> resultado;
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    Viaje* viaje = mv->find(codigo);
    if (viaje == NULL)
        return resultado;
    std::vector<Reserva*> reservas = viaje->getReservas();
    for (unsigned  i = 0; i < reservas.size(); i++) {
        Pasajero* p =
            reservas[i]->getPasajero();
        if (p->getNickname() != nicknameRecordado) {
            resultado.push_back(DTUsuarioViaje(p->getNickname(),UsuarioPasajero));
        }
    }
    codigoRecordado = codigo;
    return resultado;
}

bool ControladorCalificacion::calificarUsuario(std::string, int) {
    return false;
}