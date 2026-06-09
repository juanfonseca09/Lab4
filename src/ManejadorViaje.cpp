#include "../include/ManejadorViaje.h"
#include "../include/Viaje.h"

ManejadorViaje* ManejadorViaje::instancia = NULL;

ManejadorViaje::ManejadorViaje() {
    ultimoCodigo = 0;
}

ManejadorViaje* ManejadorViaje::getInstance() {
    if (instancia == NULL)
        instancia = new ManejadorViaje();
    return instancia;
}

void ManejadorViaje::agregarViaje(Viaje* v) {
    if (v != NULL)
        viajes[v->getCodigo()] = v;
}

Viaje* ManejadorViaje::find(int codigo) {
    std::map<int, Viaje*>::iterator it = viajes.find(codigo);
    if (it == viajes.end())
        return NULL;
    return it->second;
}

bool ManejadorViaje::existeViaje(int codigo) {
    return find(codigo) != NULL;
}

int ManejadorViaje::generarCodigo() {
    ultimoCodigo++;
    return ultimoCodigo;
}

std::map<int, Viaje*> ManejadorViaje::getViajes() {
    return viajes;
}

void ManejadorViaje::eliminarViaje(int codigo) {
    std::map<int, Viaje*>::iterator it = viajes.find(codigo);
    if (it != viajes.end()) {
        delete it->second;
        viajes.erase(it);
    }
}