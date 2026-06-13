#include "../include/ManejadorViaje.h"

ManejadorViaje* ManejadorViaje::instancia = NULL;

ManejadorViaje::ManejadorViaje() {
    ultimoCodigo = 0;
}

ManejadorViaje* ManejadorViaje::getInstance() {
    if (instancia == NULL) {
        instancia = new ManejadorViaje();
    }

    return instancia;
}

Viaje* ManejadorViaje::createViaje(
    Vehiculo* vehiculo,
    DTFecha fecha,
    std::string origen,
    std::string destino,
    int asientosPublicados,
    float precio
) {
    ultimoCodigo++;

    Viaje* viaje = new Viaje(
        ultimoCodigo,
        vehiculo,
        fecha,
        origen,
        destino,
        asientosPublicados,
        precio
    );

    viajes[ultimoCodigo] = viaje;

    return viaje;
}

void ManejadorViaje::agregarViaje(Viaje* viaje) {
    if (viaje != NULL) {
        viajes[viaje->getCodigo()] = viaje;

        if (viaje->getCodigo() > ultimoCodigo) {
            ultimoCodigo = viaje->getCodigo();
        }
    }
}

Viaje* ManejadorViaje::find(int codigo) {
    std::map<int, Viaje*>::iterator it = viajes.find(codigo);

    if (it == viajes.end()) {
        return NULL;
    }

    return it->second;
}

std::map<int, Viaje*> ManejadorViaje::getViajes() {
    return viajes;
}

void ManejadorViaje::eliminarViaje(int codigo) {
    std::map<int, Viaje*>::iterator it = viajes.find(codigo);

    if (it == viajes.end()) {
        return;
    }

    delete it->second;
    viajes.erase(it);
}