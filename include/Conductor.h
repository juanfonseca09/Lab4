#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "Usuario.h"
#include "TipoLibreta.h"
#include "TipoVehiculo.h"
#include "Vehiculo.h"

#include <set>
#include <vector>
#include <string>

class Conductor : public Usuario {
private:
    std::set<TipoLibreta> libretas;
    std::vector<Vehiculo*> vehiculos;

public:
    Conductor(std::string nickname, std::string nombre, std::string contrasena, std::string email, std::set<TipoLibreta> libs);
    virtual ~Conductor();

    std::set<TipoLibreta> getLibretas();

    bool tieneLibreta(TipoLibreta libreta);
    bool puedeConducir(TipoVehiculo tipoVehiculo);

    bool agregarVehiculo(Vehiculo* vehiculo);
    Vehiculo* buscarVehiculo(std::string matricula);
    bool tieneVehiculo(std::string matricula);

    std::vector<Vehiculo*> getVehiculos();
};

#endif