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
    ~Conductor();

    std::set<TipoLibreta> getLibretas() const;

    bool tieneLibreta(TipoLibreta libreta) const;
    bool puedeConducir(TipoVehiculo tipoVehiculo) const;

    bool agregarVehiculo(Vehiculo* vehiculo);
    Vehiculo* buscarVehiculo(std::string matricula) const;
    bool tieneVehiculo(std::string matricula) const;

    std::vector<Vehiculo*> getVehiculos() const;
};

#endif