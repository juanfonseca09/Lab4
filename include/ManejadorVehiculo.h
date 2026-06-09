#ifndef MANEJADOR_VEHICULO_H
#define MANEJADOR_VEHICULO_H

#include <map>
#include <string>

class Vehiculo;

class ManejadorVehiculo {
private:
    static ManejadorVehiculo* instancia;
    std::map<std::string, Vehiculo*> vehiculos;
    ManejadorVehiculo();
public:
    static ManejadorVehiculo* getInstance();
    void agregarVehiculo(Vehiculo* v);
    Vehiculo* find(std::string matricula);
    bool existeVehiculo(std::string matricula);
    std::map<std::string, Vehiculo*> getVehiculos();
};

#endif