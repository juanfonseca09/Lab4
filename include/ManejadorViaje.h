#ifndef MANEJADOR_VIAJE_H
#define MANEJADOR_VIAJE_H

#include <map>

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
    void agregarViaje(Viaje* v);
    Viaje* find(int codigo);
    bool existeViaje(int codigo);
    int generarCodigo();
    std::map<int, Viaje*> getViajes();
    void eliminarViaje(int codigo);
};

#endif
