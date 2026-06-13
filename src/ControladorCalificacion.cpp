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
#include "../include/ManejadorCalificacion.h"
#include "../include/Calificacion.h"
#include "../include/ControladorFechaActual.h"

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

bool ControladorCalificacion::calificarUsuario(std::string nicknameCalificado, int puntaje) {
    if (codigoRecordado == -1 || nicknameRecordado == "")
        return false;

    ManejadorCalificacion* mc = ManejadorCalificacion::getInstance();
    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mv = ManejadorViaje::getInstance();

    Usuario* evaluador = mu->find(nicknameRecordado);
    Usuario* evaluado = mu->find(nicknameCalificado);
    if (evaluador == NULL || evaluado == NULL)
        return false;

    Viaje* viaje = mv->find(codigoRecordado);
    if (viaje == NULL)
        return false;

    std::vector<Calificacion*> existentes = mc->getCalificaciones();
    for (size_t i = 0; i < existentes.size(); ++i) {
        Calificacion* c = existentes[i];
        if (c == NULL) continue;
        if (c->esDePara(nicknameRecordado, nicknameCalificado)) {
            Reserva* r = c->getReserva();
            if (r != NULL && r->getViaje() != NULL && r->getViaje()->getCodigo() == codigoRecordado)
                return false;
        }
    }

    Reserva* reservaVinculada = NULL;
    Pasajero* pasajeroEvaluador = dynamic_cast<Pasajero*>(evaluador);
    if (pasajeroEvaluador != NULL) {
        std::vector<Reserva*> reservas = pasajeroEvaluador->getReservas();
        for (size_t i = 0; i < reservas.size(); ++i) {
            if (reservas[i] != NULL && reservas[i]->getViaje() != NULL && reservas[i]->getViaje()->getCodigo() == codigoRecordado) {
                reservaVinculada = reservas[i];
                break;
            }
        }
    } else {
        reservaVinculada = viaje->buscarReservaDePasajero(nicknameCalificado);
    }

    DTFecha fechaActual = ControladorFechaActual::getInstance()->getFecha();
    Calificacion* nueva = new Calificacion(fechaActual, puntaje, evaluador, evaluado, reservaVinculada);

    mc->agregarCalificacion(nueva);
    evaluador->agregarCalificacionRealizada(nueva);
    evaluado->agregarCalificacionRecibida(nueva);
    if (reservaVinculada != NULL) {
        reservaVinculada->agregarCalificacion(nueva);
    }

    return true;
}

// Para cargarDatos
void ControladorCalificacion::recordarCodigoViaje(int codigo) {
    codigoRecordado = codigo;
}

void ControladorCalificacion::recordarUsuarioCalificador(std::string nickname) {
    nicknameRecordado = nickname;
}