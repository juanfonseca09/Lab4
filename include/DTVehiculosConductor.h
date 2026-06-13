#ifndef DT_VEHICULOS_CONDUCTOR_H
#define DT_VEHICULOS_CONDUCTOR_H

#include <string>

class DTVehiculosConductor {
private:
    std::string matricula;
    std::string marca;
    int capacidad;

public:
    DTVehiculosConductor();
    DTVehiculosConductor(std::string matricula, std::string marca, int capacidad);

    std::string getMatricula() const;
    std::string getMarca() const;
    int getCapacidad() const;
};

#endif