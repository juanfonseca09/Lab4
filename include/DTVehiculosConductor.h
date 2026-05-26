#ifndef DT_VEHICULOS_CONDUCTOR_H
#define DT_VEHICULOS_CONDUCTOR_H

#include <vector>
#include "DTDetalleVehiculo.h"

class DTVehiculosConductor {
private:
    std::vector<DTDetalleVehiculo> vehiculos;

public:
    DTVehiculosConductor(std::vector<DTDetalleVehiculo> vehiculos);

    std::vector<DTDetalleVehiculo> getVehiculos();
};

#endif