#include "../include/ControladorCalificacion.h"
#include "../include/ManejadorUsuario.h"
#include "../include/ManejadorViaje.h"
#include "../include/ManejadorCalificacion.h"
#include "../include/ControladorFechaActual.h"
#include "../include/Usuario.h"
#include "../include/Pasajero.h"
#include "../include/Conductor.h"
#include "../include/Vehiculo.h"
#include "../include/Viaje.h"
#include "../include/Reserva.h"
#include "../include/Calificacion.h"

#include <map>
#include <vector>

ControladorCalificacion* ControladorCalificacion::instancia = NULL;

static bool usuarioParticipaEnViaje(Viaje* viaje, std::string nickname) {
    if (viaje == NULL) {
        return false;
    }

    Vehiculo* vehiculo = viaje->getVehiculo();

    if (vehiculo != NULL &&
        vehiculo->getConductor() != NULL &&
        vehiculo->getConductor()->getNickname() == nickname) {
        return true;
    }

    std::vector<Reserva*> reservas = viaje->getReservas();

    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i] != NULL && reservas[i]->perteneceAPasajero(nickname)) {
            return true;
        }
    }

    return false;
}

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

    /*
     * Primero conductores, como espera la salida de prueba.
     */
    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Conductor* conductor = dynamic_cast<Conductor*>(it->second);

        if (conductor != NULL) {
            resultado.push_back(DTUsuario(
                conductor->getNickname(),
                conductor->getNombre()
            ));
        }
    }

    /*
     * Despues pasajeros.
     */
    for (it = usuarios.begin(); it != usuarios.end(); ++it) {
        Pasajero* pasajero = dynamic_cast<Pasajero*>(it->second);

        if (pasajero != NULL) {
            resultado.push_back(DTUsuario(
                pasajero->getNickname(),
                pasajero->getNombre()
            ));
        }
    }

    return resultado;
}

std::vector<DTListarViaje> ControladorCalificacion::listarViajes(std::string nickname) {
    std::vector<DTListarViaje> resultado;

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    Usuario* u = mu->find(nickname);

    nicknameRecordado = "";
    codigoRecordado = -1;

    if (u == NULL) {
        return resultado;
    }

    Pasajero* pasajero = dynamic_cast<Pasajero*>(u);

    if (pasajero != NULL) {
        std::vector<Reserva*> reservas = pasajero->getReservas();

        for (unsigned int i = 0; i < reservas.size(); i++) {
            if (reservas[i] == NULL || reservas[i]->getViaje() == NULL) {
                continue;
            }

            Viaje* v = reservas[i]->getViaje();
            Vehiculo* vehiculo = v->getVehiculo();

            if (vehiculo == NULL || vehiculo->getConductor() == NULL) {
                continue;
            }

            resultado.push_back(
                DTListarViaje(
                    v->getCodigo(),
                    v->getFecha(),
                    v->getOrigen(),
                    v->getDestino(),
                    vehiculo->getConductor()->getNickname()
                )
            );
        }
    } else {
        Conductor* conductor = dynamic_cast<Conductor*>(u);

        if (conductor != NULL) {
            std::vector<Vehiculo*> vehiculos = conductor->getVehiculos();

            for (unsigned int i = 0; i < vehiculos.size(); i++) {
                if (vehiculos[i] == NULL) {
                    continue;
                }

                std::vector<Viaje*> viajes = vehiculos[i]->getViajes();

                for (unsigned int j = 0; j < viajes.size(); j++) {
                    if (viajes[j] != NULL) {
                        resultado.push_back(
                            DTListarViaje(
                                viajes[j]->getCodigo(),
                                viajes[j]->getFecha(),
                                viajes[j]->getOrigen(),
                                viajes[j]->getDestino(),
                                conductor->getNickname()
                            )
                        );
                    }
                }
            }
        }
    }

    nicknameRecordado = nickname;
    return resultado;
}

std::vector<DTUsuarioViaje> ControladorCalificacion::listarUsuariosViaje(int codigo) {
    std::vector<DTUsuarioViaje> resultado;

    ManejadorViaje* mv = ManejadorViaje::getInstance();
    Viaje* viaje = mv->find(codigo);

    codigoRecordado = -1;

    if (viaje == NULL) {
        return resultado;
    }

    Vehiculo* vehiculo = viaje->getVehiculo();

    if (vehiculo != NULL && vehiculo->getConductor() != NULL) {
        Conductor* conductor = vehiculo->getConductor();

        if (conductor->getNickname() != nicknameRecordado) {
            resultado.push_back(DTUsuarioViaje(conductor->getNickname(), UsuarioConductor));
        }
    }

    std::vector<Reserva*> reservas = viaje->getReservas();

    for (unsigned int i = 0; i < reservas.size(); i++) {
        if (reservas[i] == NULL || reservas[i]->getPasajero() == NULL) {
            continue;
        }

        Pasajero* p = reservas[i]->getPasajero();

        if (p->getNickname() != nicknameRecordado) {
            resultado.push_back(DTUsuarioViaje(p->getNickname(), UsuarioPasajero));
        }
    }

    codigoRecordado = codigo;
    return resultado;
}

bool ControladorCalificacion::calificarUsuario(std::string nicknameCalificado, int puntaje) {
    if (codigoRecordado == -1 || nicknameRecordado == "") {
        return false;
    }

    if (puntaje < 1 || puntaje > 5) {
        return false;
    }

    if (nicknameRecordado == nicknameCalificado) {
        return false;
    }

    ManejadorUsuario* mu = ManejadorUsuario::getInstance();
    ManejadorViaje* mv = ManejadorViaje::getInstance();
    ManejadorCalificacion* mc = ManejadorCalificacion::getInstance();

    Usuario* evaluador = mu->find(nicknameRecordado);
    Usuario* evaluado = mu->find(nicknameCalificado);
    Viaje* viaje = mv->find(codigoRecordado);

    if (evaluador == NULL || evaluado == NULL || viaje == NULL) {
        return false;
    }

    if (!usuarioParticipaEnViaje(viaje, nicknameRecordado)) {
        return false;
    }

    if (!usuarioParticipaEnViaje(viaje, nicknameCalificado)) {
        return false;
    }

    std::vector<Calificacion*> existentes = mc->getCalificaciones();

    for (unsigned int i = 0; i < existentes.size(); i++) {
        Calificacion* c = existentes[i];

        if (c == NULL) {
            continue;
        }

        Reserva* r = c->getReserva();

        if (c->esDePara(nicknameRecordado, nicknameCalificado) &&
            r != NULL &&
            r->getViaje() != NULL &&
            r->getViaje()->getCodigo() == codigoRecordado) {
            return false;
        }
    }

    Reserva* reservaVinculada = NULL;
    Pasajero* pasajeroEvaluador = dynamic_cast<Pasajero*>(evaluador);

    if (pasajeroEvaluador != NULL) {
        reservaVinculada = viaje->buscarReservaDePasajero(nicknameRecordado);
    } else {
        reservaVinculada = viaje->buscarReservaDePasajero(nicknameCalificado);
    }

    if (reservaVinculada == NULL) {
        return false;
    }

    DTFecha fechaActual = ControladorFechaActual::getInstance()->getFecha();
    Calificacion* nueva = new Calificacion(fechaActual, puntaje, evaluador, evaluado, reservaVinculada);

    mc->agregarCalificacion(nueva);
    evaluador->agregarCalificacionRealizada(nueva);
    evaluado->agregarCalificacionRecibida(nueva);
    reservaVinculada->agregarCalificacion(nueva);

    return true;
}

void ControladorCalificacion::recordarCodigoViaje(int codigo) {
    codigoRecordado = codigo;
}

void ControladorCalificacion::recordarUsuarioCalificador(std::string nickname) {
    nicknameRecordado = nickname;
}