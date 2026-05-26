#include "../include/DTVehiculosConductor.h"

DTVehiculosConductor::DTVehiculosConductor(std::vector<DTDetalleVehiculo> vehiculos)
    {
    this->vehiculos = vehiculos;
}

std::vector<DTDetalleVehiculo> DTVehiculosConductor::getVehiculos() {
    return vehiculos;
}
