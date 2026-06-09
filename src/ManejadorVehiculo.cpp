#include "../include/ManejadorVehiculo.h"
#include "../include/Vehiculo.h"

ManejadorVehiculo* ManejadorVehiculo::instancia = NULL;

ManejadorVehiculo::ManejadorVehiculo() {
}

ManejadorVehiculo* ManejadorVehiculo::getInstance() {
    if (instancia == NULL)
        instancia = new ManejadorVehiculo();
    return instancia;
}

void ManejadorVehiculo::agregarVehiculo(Vehiculo* v) {
    if (v != NULL)
        vehiculos[v->getMatricula()] = v;
}

Vehiculo* ManejadorVehiculo::find(std::string matricula) {
    std::map<std::string, Vehiculo*>::iterator it;
    it = vehiculos.find(matricula);
    if (it == vehiculos.end())
        return NULL;
    return it->second;
}

bool ManejadorVehiculo::existeVehiculo(std::string matricula) {
    return find(matricula) != NULL;
}

std::map<std::string, Vehiculo*> ManejadorVehiculo::getVehiculos() {
    return vehiculos;
}