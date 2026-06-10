#ifndef MANEJADOR_VIAJE_H
#define MANEJADOR_VIAJE_H

#include <map>
#include "Viaje.h"

class Viaje;

class ManejadorViaje {
private:
    static ManejadorViaje* instancia;
    std::map<int, Viaje*> viajes;
    int ultimoCodigo;
    ManejadorViaje();
public:
    ~ManejadorViaje();
    static ManejadorViaje* getInstance();
    Viaje* createViaje(Vehiculo* vehiculo, DTFecha fecha, std::string origen, std::string destino, int asientos, float precio);
    void agregarViaje(Viaje* v);
    Viaje* find(int codigo);
    bool existeViaje(int codigo);
    int generarCodigo();
    std::map<int, Viaje*> getViajes();
    void eliminarViaje(int codigo);
};

#endif
