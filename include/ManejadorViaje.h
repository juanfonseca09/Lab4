#ifndef MANEJADOR_VIAJE_H
#define MANEJADOR_VIAJE_H

#include "Viaje.h"
#include "Vehiculo.h"
#include "DTFecha.h"

#include <map>

class ManejadorViaje {
private:
    static ManejadorViaje* instancia;

    std::map<int, Viaje*> viajes;
    int ultimoCodigo;

    ManejadorViaje();

public:
    static ManejadorViaje* getInstance();

    Viaje* createViaje(
        Vehiculo* vehiculo,
        DTFecha fecha,
        std::string origen,
        std::string destino,
        int asientosPublicados,
        float precio
    );

    void agregarViaje(Viaje* viaje);

    Viaje* find(int codigo);

    std::map<int, Viaje*> getViajes();

    void eliminarViaje(int codigo);
};

#endif